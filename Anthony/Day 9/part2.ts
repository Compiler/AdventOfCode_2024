import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let diskMap = input.trim();

// Make a list of files and list of gaps
const files = [];
const gaps = [];
let startIndex = 0;
for (let i = 0; i < diskMap.length; i++) {
	const size = parseInt(diskMap[i]);
	if (i % 2 === 0) {
		files.push({ startIndex, size, fileId: i / 2 });
	} else {
		gaps.push({ startIndex, size })
	}
	startIndex += size;
}

// Move files into gaps as appropriate
// Note we're not trying to find optimal packing, just going through the list of files in reverse order
// (that's what the problem told us to do)
// I think that actually means this n^2 solution is actually optimal,
// since I can't do stuff like organize the files/gaps by size to eliminate the linear search
for (let i = files.length - 1; i >= 0; i--) {
	const file = files[i];
	for (let j = 0; j < gaps.length; j++) {
		const gap = gaps[j];
		if (file.startIndex < gap.startIndex || file.size > gap.size) {
			continue;
		}
		file.startIndex = gap.startIndex;
		if (gap.size === file.size) {
			gaps.splice(j, 1);
		} else {
			gap.startIndex += file.size;
			gap.size -= file.size;
		}
		break;
	}
}

// Calculate checksum file-by-file
const checksum = files.reduce((acc, { startIndex, size, fileId }) => {
	const indicesSum = size * (startIndex * 2 + (size - 1)) / 2;
	return acc + indicesSum * fileId;
}, 0);

console.log(checksum);
