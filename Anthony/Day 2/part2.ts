import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let totalSafe = 0;
for (const report of input.split("\r\n")) {
	const levels = report.split(" ").map(level => parseInt(level));
	if (levels.length >= 2 && checkSafe(levels)) {
		totalSafe++;
	}
	console.log();
}

console.log(totalSafe);

function evalDirection(levels) {
	if (levels[1] < levels[0]) {
		return { minDiff: -3, maxDiff: -1, arrow: '↓' };
	} else {
		return { minDiff: 1, maxDiff: 3, arrow: '↑' };
	}
}

function checkSafe(levels, hasSkipped = false) {
	const { minDiff, maxDiff, arrow } = evalDirection(levels);
	console.log(`Trying ${arrow} ${levels.join(" ")}`);

	let prevLevel = levels[0];
	let index = 0;
	for (const level of levels.slice(1)) {
		const diff = level - prevLevel;
		if (diff < minDiff || diff > maxDiff) {
			let cause;
			if (diff === 0) {
				cause = "SAME";
			} else if (diff / maxDiff > 0) {
				cause = "TOO FAR";
			} else {
				cause = "WRONG DIRECTION";
			}
			console.log(`Failed at index ${index + 1}: ${cause}(${diff})`);
			if (hasSkipped) {
				return false;
			}

			// I was pretty sure you only needed to check this digit and the previous,
			// but [4, 1, 3, 5] shows where it fails when checking 3 and needs to remove the 4
			// So I check 3 digits back, which handles that case - and it _actually_ shouldn't
			// be possible for the issue to be further back than that

			// Try removing this digit
			if (checkSafe([...levels.slice(0, index + 1), ...levels.slice(index + 2)], true)) {
				console.log("SAFE");
				return true;
			}
			// Try removing previous digit
			if (checkSafe([...levels.slice(0, index), ...levels.slice(index + 1)], true)) {
				console.log("SAFE");
				return true;
			}
			// Try removing another previous digit
			if (index > 0 && checkSafe([...levels.slice(0, index - 1), ...levels.slice(index)], true)) {
				console.log("SAFE");
				return true;
			}
			// Digits before that shouldn't matter
			console.log("UNSAFE");
			return false;
		}
		prevLevel = level;
		index++;
	}
	if (!hasSkipped) {
		console.log("SAFE");
	}
	return true;
}
