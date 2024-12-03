import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let sum = 0;
for (const [_, left, right] of input.matchAll(/mul\((\d{1,3}),(\d{1,3})\)/g)) {
	sum += parseInt(left) * parseInt(right);
}

console.log(sum);
