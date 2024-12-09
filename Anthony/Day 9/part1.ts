import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let diskMap = input.trim();

// Calculate the checksum, pulling numbers from the right to fill empty space
let checksum = 0;
let totalBlocks = 0;
for (let i = 0; i < diskMap.length; i++) {
	let numBlocks = parseInt(diskMap[i]);
	console.log("\nRemoving", numBlocks, "at index", i)
	if (i % 2 === 0) {
		// The file ID (i / 2) times the block index
		handleChunk(numBlocks, i / 2);
	} else {
		// Empty space
		// Break it up into chunks of size numBlocks or diskMap[diskMap.length - 1], whichever is smaller
		// Whenever diskMap[diskMap.length - 1] is 0, remove the last two indices (the second to last index is empty space)
		while (numBlocks > 0) {
			const blocksRemaining = parseInt(diskMap[diskMap.length - 1]);
			const chunkBlocks = Math.min(numBlocks, blocksRemaining);
			handleChunk(chunkBlocks, diskMap.length / 2 - 0.5);
			console.log("removing chunk of", chunkBlocks, "from", blocksRemaining, `(${diskMap.slice(-10)})`);
			numBlocks -= chunkBlocks;
			if (blocksRemaining === chunkBlocks) {
				console.log("removing block from end");
				diskMap = diskMap.slice(0, -2);
			} else {
				diskMap = `${diskMap.slice(0, -1)}${blocksRemaining - chunkBlocks}`;
			}
		}
	}
}

function handleChunk(numBlocks, fileId) {
	// we can do all the indices at once by summing the sequence of numbers from totalBlocks to totalBlocks + diskMap[i]
	const indicesSum = numBlocks * (totalBlocks * 2 + (numBlocks - 1)) / 2;
	console.log("handling chunk", numBlocks, totalBlocks, indicesSum)
	checksum += indicesSum * fileId;
	totalBlocks += numBlocks;
}

console.log("\nchecksum:", checksum);
