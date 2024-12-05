import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let stringToSearchFor = "XMAS";
let foundStrings = 0;

// I tried thinking of something besides the naive approach here, but couldn't come up with anything

const wordSearch = input.trim().split("\r\n");
const rows = wordSearch.length;
const cols = wordSearch[0].length;
for (let row = 0; row < rows; row++) {
	for (let col = 0; col < cols; col++) {
		if (wordSearch[row][col] !== "X") {
			continue;
		}

		for (let dx = -1; dx <= 1; dx++) {
			if (wordSearch[0][col + dx * (stringToSearchFor.length - 1)] == null) {
				continue;
			}

			for (let dy = -1; dy <= 1; dy++) {
				if (dx === 0 && dy === 0) {
					continue;
				}

				if (wordSearch[row + dy * (stringToSearchFor.length - 1)] == null) {
					continue;
				}

				if (checkString(row, col, dx, dy)) {
					console.log(`Found "${stringToSearchFor}" going ${["north", "", "south"][dy + 1]}${["west", "", "east"][dx + 1]} from ${col + 1}, ${row + 1}`);
					foundStrings++;
				}
			}
		}
	}
}

// Search for the string starting at a given index and moving in the given direction
function checkString(row, col, dx, dy) {
	for (let character of stringToSearchFor) {
		if (wordSearch[row][col] !== character) {
			return false;
		}
		row += dy;
		col += dx;
	}

	return true;
}

console.log(foundStrings);
