import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

// Thought the sorting was unnecessary and we could actually just sum each and find the difference
// hence leftSum and rightSum
// That got the wrong answer, so I did the obvious/naive solution of sorting both lists and summing the differences

// Attemp 1: Subtract the sums
let leftSum = 0, rightSum = 0;
for (const [_, left, right] of input.matchAll(/^(\d+)\s*(\d+)$/gm)) {
	leftSum += parseInt(left);
	rightSum += parseInt(right);
}
console.log(Math.abs(leftSum - rightSum));

// Attempt 2: Sum the differences
let allLeft = [], allRight = [];
for (const [_, left, right] of input.matchAll(/^(\d+)\s*(\d+)$/gm)) {
	allLeft.push(parseInt(left));
	allRight.push(parseInt(right));
}
allLeft.sort();
allRight.sort();
console.log(allLeft.reduce((acc, curr, i) => acc + Math.abs(curr - allRight[i]), 0))
