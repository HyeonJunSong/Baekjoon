const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const n = inp[0][0];

const leftSum = new Map();
for (let i = 0; i < n; i++)
  for (let j = 0; j < n; j++)
    leftSum.set(
      inp[1 + i][0] + inp[1 + j][1],
      (leftSum.get(inp[1 + i][0] + inp[1 + j][1]) ?? 0) + 1
    );

let ans = 0;
for (let i = 0; i < n; i++)
  for (let j = 0; j < n; j++) ans += leftSum.get(-(inp[1 + i][2] + inp[1 + j][3])) ?? 0;

console.log(ans);
