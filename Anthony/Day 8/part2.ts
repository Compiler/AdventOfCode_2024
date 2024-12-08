import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

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

// gcd and lcm taken from https://www.geeksforgeeks.org/javascript-program-to-find-lcm-of-two-numbers/
function gcd(a, b) { 
    for (let temp = b; b !== 0;) { 
        b = a % b; 
        a = temp; 
        temp = b; 
    } 
    return a; 
}

const antinodesMap = new Array(rows.length).fill(0).map(_ => new Array(rows[0].length).fill(false));
let uniqueAntinodes = 0;
Object.keys(freqMap).forEach(freq => {
	const locations = freqMap[freq];
	const freqMapAntinodesMap = new Array(rows.length).fill(0).map(_ => new Array(rows[0].length).fill(false));
	for (let i = 0; i < locations.length - 1; i++) {
		for (let j = i + 1; j < locations.length; j++) {
			const left = locations[i];
			const right = locations[j];
			const diff = { x: left.col - right.col, y: left.row - right.row };
			const denom = gcd(diff.x, diff.y);
			diff.x /= denom;
			diff.y /= denom;
			console.log(freq, left, right, denom, diff);

			let x = left.col, y = left.row;
			while (x >= 0 && y >= 0 && y < rows.length && x < rows[0].length) {
				if (antinodesMap[y]?.[x] === false) {
					uniqueAntinodes++;
					antinodesMap[y][x] = true;
				}
				freqMapAntinodesMap[y][x] = true;
				x += diff.x;
				y += diff.y;
			}
			x = right.col, y = right.row;
			while (x >= 0 && y >= 0 && y < rows.length && x < rows[0].length) {
				if (antinodesMap[y]?.[x] === false) {
					uniqueAntinodes++;
					antinodesMap[y][x] = true;
				}
				freqMapAntinodesMap[y][x] = true;
				x -= diff.x;
				y -= diff.y;
			}
		}
	}
	rows.forEach((string, row) => {
		for (let col = 0; col < string.length; col++) {
			if (string[col] !== freq) {
				if (freqMapAntinodesMap[row][col]) {
					string = [...string.slice(0, col), '#', ...string.slice(col + 1)].join("");
				} else {
					string = [...string.slice(0, col), '.', ...string.slice(col + 1)].join("");
				}
			}
		}
		console.log(string);
	});
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

// 753 too low