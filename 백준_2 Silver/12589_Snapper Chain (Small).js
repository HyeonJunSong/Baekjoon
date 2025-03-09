const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let idx = 0;
const [T] = inp[idx++];

function testCase() {
  const [N, T] = inp[idx++];
  return T % 2 ** N === 2 ** N - 1 ? "ON" : "OFF";
}

for (let i = 0; i < T; i++) console.log(`Case #${i + 1}: ${testCase()}`);
