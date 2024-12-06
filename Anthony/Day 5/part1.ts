import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

// Naive solution would be to make a dict of numbers to an array of their deps
// Checking each list of updates would then mean comparing each of those numbers against all numbers already checked
// Instead we can build a dependency tree and maintain a list of met dependencies, and check each number against that instead

const dependencies: Record<number, {
	dependencies: Set<number>;
	dependents: Set<number>;
}> = {};

const [dependenciesList, updatesList] = input.split("\r\n\r\n");

dependenciesList.split("\r\n").forEach(dependency => {
	const [left, right] = dependency.split("|");
	const leftInt = parseInt(left);
	const rightInt = parseInt(right);

	dependencies[rightInt] ??= {
		dependencies: new Set(),
		dependents: new Set()
	};
	dependencies[rightInt].dependencies.add(leftInt);
});

// Optimize dependencies
// There's a dependency cycle ;_;
// I didn't want to spend more time on this problem, so I just removed it
// I spent so long before realizing that, and all my optimizations depended on there not being a cycle
// Object.keys(dependencies).forEach(dependency => {
// 	const dep = parseInt(dependency);
// 	const allDependencies = new Set<number>();

// 	function findDependencies(dependency: number) {
// 		if (!allDependencies.has(dependency)) {
// 			allDependencies.add(dependency);
// 			[...dependencies[dependency].dependencies].forEach(findDependencies);
// 		}
// 	}
// 	[...dependencies[dep].dependencies].forEach(findDependencies);

// 	dependencies[dep].dependencies = dependencies[dep].dependencies.difference(allDependencies);
// });

// Fill out dependents
// Object.keys(dependencies).forEach(dependency => {
// 	const dep = parseInt(dependency);
// 	dependencies[dep].dependencies.forEach(d => dependencies[d].dependents.add(dep));
// });
// console.log(dependencies);

let sum = 0;
updatesList.trim().split("\r\n").forEach(update => {
	// const metDependencies = new Set<number>();
	// const dependenciesAlreadyMet: Record<number, number> = {};
	// function checkDependents(page: number) {
	// 	[...dependencies[page].dependents].forEach(dependent => {
	// 		dependenciesAlreadyMet[dependent] ??= 0;
	// 		dependenciesAlreadyMet[dependent]++;
	// 		if (dependenciesAlreadyMet[dependent] === dependencies[dependent].dependencies.size) {
	// 			metDependencies.add(dependent);
	// 			checkDependents(dependent);
	// 		}
	// 	})
	// }

	const pages = update.trim().split(",").map(page => parseInt(page));
	const seenPages = new Set<number>();
	const validUpdate = pages.every(page => {
		// if (page in dependencies && !metDependencies.has(page)) {
		// 	return false;
		// }
		// checkDependents(page);
		// return true;

		if (page in dependencies) {
			// This is so inefficient ;_;
			if ([...dependencies[page].dependencies].some(dependency => pages.includes(dependency) && !seenPages.has(dependency))) {
				return false;
			}
		}
		seenPages.add(page);
		return true;
	});
	if (validUpdate) {
		sum += pages[Math.floor(pages.length / 2)];
	}
});

console.log(sum);
