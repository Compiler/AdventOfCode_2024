import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

// This time we make a frequency map of the right values
let allLeft = [], rightFreq = {};
for (const [_, left, right] of input.matchAll(/^(\d+)\s*(\d+)$/gm)) {
	const leftInt = parseInt(left);
	const rightInt = parseInt(right);
	rightFreq[rightInt] = (rightFreq[rightInt] ?? 0) + 1;
	allLeft.push(leftInt);
}

const similarity = allLeft.reduce((acc, curr) => acc + (curr * (rightFreq[curr] ?? 0)), 0);
console.log(similarity);
