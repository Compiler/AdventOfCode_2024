import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let foundStrings = 0;

// I tried thinking of something besides the naive approach here, but couldn't come up with anything

const wordSearch = input.trim().split("\r\n");
const rows = wordSearch.length;
const cols = wordSearch[0].length;
for (let row = 1; row < rows - 1; row++) {
	for (let col = 1; col < cols - 1; col++) {
		if (wordSearch[row][col] !== "A") {
			continue;
		}

		const northWest = wordSearch[row - 1][col - 1];
		const northEast = wordSearch[row - 1][col + 1];
		const southWest = wordSearch[row + 1][col - 1];
		const southEast = wordSearch[row + 1][col + 1];

		const forwardValid = (northWest === "M" && southEast === "S") || (northWest === "S" && southEast === "M");
		const backwardsValid = (northEast === "M" && southWest === "S") || (northEast === "S" && southWest === "M");

		if (forwardValid && backwardsValid) {
			console.log(`Found "X-MAS" centered on ${col + 1}, ${row + 1}`);
			foundStrings++;
		}
	}
}

console.log(foundStrings);
