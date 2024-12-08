import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

// Create list of positions for each frequency
// Add list of unique antinode locations by looking at each pair of locations
//   - each pair has an antinode taken by adding the difference of the positions to each node

const freqMap = {};
const rows = input.trim().split("\r\n");
rows.forEach((string, row) => {
	for (let col = 0; col < string.length; col++) {
		if (string[col] === ".") {
			continue;
		}
		const freq = string[col];
		freqMap[freq] ??= [];
		freqMap[freq].push({ row, col });
	}
});

const antinodesMap = new Array(rows.length).fill(0).map(_ => new Array(rows[0].length).fill(false));
let uniqueAntinodes = 0;
Object.keys(freqMap).forEach(freq => {
	const locations = freqMap[freq];
	for (let i = 0; i < locations.length - 1; i++) {
		for (let j = i + 1; j < locations.length; j++) {
			const left = locations[i];
			const right = locations[j];
			const diff = { x: left.col - right.col, y: left.row - right.row };
			if (antinodesMap[left.row + diff.y]?.[left.col + diff.x] === false) {
				uniqueAntinodes++;
				antinodesMap[left.row + diff.y][left.col + diff.x] = true;
			}
			if (antinodesMap[right.row - diff.y]?.[right.col - diff.x] === false) {
				uniqueAntinodes++;
				antinodesMap[right.row - diff.y][right.col - diff.x] = true;
			}
		}
	}
});

rows.forEach((string, row) => {
	for (let col = 0; col < string.length; col++) {
		if (string[col] === "." && antinodesMap[row][col]) {
			string = [...string.slice(0, col), '#', ...string.slice(col + 1)].join("");
		}
	}
	console.log(string);
});
console.log(uniqueAntinodes);
