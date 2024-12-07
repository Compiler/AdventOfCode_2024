import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let x, y;
const map = input.trim().split("\r\n");
const rows = map.length;
const cols = map[0].length;

// Find start
for (let row in map) {
	const col = map[row].indexOf("^");
	if (col >= 0) {
		x = col;
		y = parseInt(row);
		break;
	}
}

console.log(`Starting at ${x}, ${y}`);

const deltas = [
	{ x:  0, y: -1 },
	{ x:  1, y:  0 },
	{ x:  0, y:  1 },
	{ x: -1, y:  0 }
];

let direction = 0; // Up
let uniqueTiles = 1;

while (x >= 0 && x < cols - 1 && y >= 0 && y < rows - 1) {
	while (map[y + deltas[direction].y][x + deltas[direction].x] === '#') {
		direction = (direction + 1) % deltas.length;
	}
	const { x: dx, y: dy } = deltas[direction];
	x += dx;
	y += dy;
	if (map[y][x] === '.') {
		map[y] = `${map[y].slice(0, x)}X${(x - 1) < cols ? map[y].slice(x + 1) : ''}`;
		uniqueTiles++;
	}
}

console.log(map.join('\n'));
console.log(uniqueTiles);
