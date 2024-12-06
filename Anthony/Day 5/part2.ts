import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

const dependencies: Record<number, Set<number>> = {};

const [dependenciesList, updatesList] = input.split("\r\n\r\n");

dependenciesList.split("\r\n").forEach(dependency => {
	const [left, right] = dependency.split("|");
	const leftInt = parseInt(left);
	const rightInt = parseInt(right);

	dependencies[rightInt] ??= new Set();
	dependencies[rightInt].add(leftInt);
});

let sum = 0;
updatesList.trim().split("\r\n").forEach(update => {
	// Since a global dependency graph won't work, but a dependency graph for each update will, let's use that approach now
	// We'll build the dep tree and then build the correctly sorted list by going through the graph for ones with no remaining dependencies
	// I don't think my optimization step from before was useful and/or applies here, so I'll skip that step

	// Build the tree
	const dependencyTree: Record<number, Set<number>> = {};
	const rawPages = update.trim().split(",").map(page => parseInt(page));
	const pages = new Set(rawPages);
	let next: number = -1;
	[...pages].forEach(page => {
		dependencyTree[page] = dependencies[page].intersection(pages);
		if (dependencyTree[page].size === 0) {
			next = page;
		}
	});

	// Determine if the current graph works, in which case don't touch it
	const seenPages = new Set<number>();
	const validUpdate = [...pages].every(page => {
		if (page in dependencies) {
			if (dependencyTree[page].difference(seenPages).size > 0) {
				return false;
			}
		}
		seenPages.add(page);
		return true;
	});

	if (!validUpdate) {
		let sortedPages = [];
		while (sortedPages.length < pages.size) {
			sortedPages.push(next);
			delete dependencyTree[next];
			const curr = next;
			Object.keys(dependencyTree).forEach(p => {
				const page = parseInt(p);
				dependencyTree[page].delete(curr);
				if (dependencyTree[page].size === 0) {
					next = page;
				}
			});
		}
		sum += sortedPages[Math.floor(sortedPages.length / 2)];
	}
});

console.log(sum);

// 10919 is too high