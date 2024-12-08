import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

const operators = [
	(a, b) => a + b,
	(a, b) => a * b,
	(a, b) => parseInt(`${a}${b}`)
];

let sum = 0;
for (let equation of input.trim().split("\r\n")) {
	const [resultString, operandsString] = equation.split(":");
	const result = parseInt(resultString);
	const operands = operandsString.trim().split(" ").map(v => parseInt(v));
	console.log("Trying to calculate", result, "with", operands)

	for (let value of generateResults(result, operands)) {
		if (value === result) {
			sum += result;
			break;
		}
	}
}

function* generateResults(target, operands) {
	if (operands[0] > target) {
		// Early exit
		return;
	}
	if (operands.length === 1) {
		yield operands[0];
		return;
	}
	for (let operator of operators) {
		yield* generateResults(target, [operator(operands[0], operands[1]), ...operands.slice(2)]);
	}
}

console.log(sum);
