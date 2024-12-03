import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let totalSafe = 0;
for (const report of input.split("\r\n")) {
	const levels = report.split(" ").map(level => parseInt(level));
	if (levels.length < 2) {
		continue;
	}
	let minDiff, maxDiff;
	if (levels[1] < levels[0]) {
		minDiff = -3;
		maxDiff = -1;
	} else {
		minDiff = 1;
		maxDiff = 3;
	}
	let isSafe = true;
	let prevLevel = levels[0];
	for (const level of levels.slice(1)) {
		const diff = level - prevLevel;
		if (diff < minDiff || diff > maxDiff) {
			isSafe = false;
			break;
		}
		prevLevel = level;
	}
	if (isSafe) {
		totalSafe++;
	}
}

console.log(totalSafe);
