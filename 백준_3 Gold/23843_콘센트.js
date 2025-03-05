const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];
const arr = inp[1];

const outlets = Array.from({ length: M }, () => 0);
arr.sort((a, b) => b - a);
for (let i = 0; i < N; i++) {
  let shortestIdx = 0;
  for (let j = 1; j < M; j++) if (outlets[j] < outlets[shortestIdx]) shortestIdx = j;
  outlets[shortestIdx] += arr[i];
}

console.log(outlets.reduce((accum, cur) => Math.max(accum, cur), -Infinity));
