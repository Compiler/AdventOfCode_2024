import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

// Make 4 maps of tiles that would cause a loop if we were to be going in a direction specific to each map.
// After turning, every tile in front and before us, up until the first obstacle, would cause a loop if going the same direction.
// After constructing those maps, go through the map again.
// At each position check if we could move to the right and cause a loop (via querying the correct map)
// If that check succeeds, we could add an obstacle directly in front of us.
// If that number fails, then I think we'll need to then check the loop actually works,
// since its possible we obstructed part of its path with the obstacle

const map = input.trim().split("\r\n");
const rows = map.length;
const cols = map[0].length;

// Find start
let startX, startY;
for (let row in map) {
	const col = map[row].indexOf("^");
	if (col >= 0) {
		startX = col;
		startY = parseInt(row);
		break;
	}
}
console.log(`Starting at ${startX}, ${startY}`);

const deltas = [
	{ x:  0, y: -1 },
	{ x:  1, y:  0 },
	{ x:  0, y:  1 },
	{ x: -1, y:  0 }
];

// const loopCausingPaths = [
// 	new Array(rows).fill(0).map(_ => new Array(cols).fill(false)),
// 	new Array(rows).fill(0).map(_ => new Array(cols).fill(false)),
// 	new Array(rows).fill(0).map(_ => new Array(cols).fill(false)),
// 	new Array(rows).fill(0).map(_ => new Array(cols).fill(false))
// ];

// // Construct our maps
// while (x >= 0 && x < cols - 1 && y >= 0 && y < rows - 1) {
// 	if (map[y + deltas[direction].y][x + deltas[direction].x] === '#') {
// 		direction = (direction + 1) % deltas.length;
		
// 		// Mark each tile behind us as loopable going this direction, up until an obstacle
// 		const { x: dx, y: dy } = deltas[direction];
// 		let tileX = x - dx, tileY = y - dy;
// 		while (tileX >= 0 && tileX < cols - 1 && tileY >= 0 && tileY < rows - 1) {
// 			if (map[tileY - dx]?.[tileX - dy] === "#") {
// 				break;
// 			}
// 			loopCausingPaths[direction][tileY][tileX] = true;
// 			tileX -= dx;
// 			tileY -= dy;
// 		}
// 	}
// 	const { x: dx, y: dy } = deltas[direction];
// 	// Mark each tile as loopable if going this direction
// 	loopCausingPaths[direction][y][x] = true;
// 	x += dx;
// 	y += dy;
// }

// Check for intersections
let possibleObstacles = 0;
const obstaclePositions = new Array(rows).fill(0).map(_ => new Array(cols).fill(false));
let x = startX, y = startY, direction = 0;
while (x >= 0 && x < cols - 1 && y >= 0 && y < rows - 1) {
	checkLoop(y + deltas[direction].y, x + deltas[direction].x);
	while (map[y + deltas[direction].y][x + deltas[direction].x] === '#') {
		direction = (direction + 1) % deltas.length;
	}
	checkLoop(y + deltas[direction].y, x + deltas[direction].x)
	const { x: dx, y: dy } = deltas[direction];
	x += dx;
	y += dy;
}

function checkLoop(obstacleY, obstacleX) {
	if (obstaclePositions[obstacleY][obstacleX]) {
		// Already found this obstacle location
		return false;
	}
	if (obstacleY === startY && obstacleX === startX) {
		// Can't put an obstacle over the starting position
		return false;
	}
	let x = startX, y = startY, direction = 0;
	// Only check turns, so we're not checking positions as often
	const seenPositions = [
		new Array(rows).fill(0).map(_ => new Array(cols).fill(false)),
		new Array(rows).fill(0).map(_ => new Array(cols).fill(false)),
		new Array(rows).fill(0).map(_ => new Array(cols).fill(false)),
		new Array(rows).fill(0).map(_ => new Array(cols).fill(false))
	];
	while (x >= 0 && x < cols - 1 && y >= 0 && y < rows - 1) {
		while (map[y + deltas[direction].y]?.[x + deltas[direction].x] === '#' ||
			(obstacleX === x + deltas[direction].x && obstacleY === y + deltas[direction].y)) {

			direction = (direction + 1) % deltas.length;
			if (seenPositions[direction][y][x]) {
				// Loop!
				// console.log(seenPositions[0].map((v, row) => v.map((v, col) => {
				// 	if (row === startY && col === startX) {
				// 		return "^";
				// 	}
				// 	if (row === obstacleY && col === obstacleX) {
				// 		return "!";
				// 	}
				// 	if (v || seenPositions[1][row][col] || seenPositions[2][row][col] || seenPositions[3][row][col]) {
				// 		return "O";
				// 	}
				// 	return map[row][col];
				// }).join("")).join("\n"));
				console.log("---", obstacleY, obstacleX);
				obstaclePositions[obstacleY][obstacleX] = true;
				possibleObstacles++;
				return true;
			}
			seenPositions[direction][y][x] = true;
		}
		const { x: dx, y: dy } = deltas[direction];
		x += dx;
		y += dy;
	}
	return false;
}

console.log(obstaclePositions.map((v, row) => v.map((v, col) => {
	if (row === startY && col === startX) {
		return "^";
	}
	if (v) {
		return "!";
	}
	return map[row][col];
}).join("")).join("\n"));
console.log(possibleObstacles);
