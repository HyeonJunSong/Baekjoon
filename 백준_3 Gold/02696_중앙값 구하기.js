const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let inpIdx = 0;
const [T] = inp[inpIdx++];

const ans = [];

function testCase() {
  const [M] = inp[inpIdx++];
  const arr = [];
  for (let i = 0; i < M / 10; i++) arr.push(...inp[inpIdx++]);

  const midVals = [];

  const lis = [];
  for (let i = 0; i < M; i++) {
    lis.push(arr[i]);
    if (i % 2 === 1) continue;
    lis.sort((a, b) => a - b);
    midVals.push(lis[Math.floor(lis.length / 2)]);
  }

  ans.push(midVals.length);
  for (let i = 0; i < midVals.length; i += 10) ans.push(midVals.slice(i, i + 10).join(" "));
}
for (let t = 0; t < T; t++) testCase();
console.log(ans.join("\n"));
