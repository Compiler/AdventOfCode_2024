import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let sum = 0;
let enabled = true;
for (const [match, left, right] of input.matchAll(/mul\((\d{1,3}),(\d{1,3})\)|don't\(\)|do\(\)/g)) {
	if (match === "don't()") {
		enabled = false;
		continue;
	}

	if (match === "do()") {
		enabled = true;
		continue;
	}

	if (enabled) {
		sum += parseInt(left) * parseInt(right);
	}
}

console.log(sum);
