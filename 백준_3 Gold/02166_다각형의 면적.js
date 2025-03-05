const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];

const points = inp.slice(1);

let ans = 0;

for (let i = 1; i < N; i++) ans += points[i - 1][0] * points[i][1];
ans += points[N - 1][0] * points[0][1];

for (let i = 1; i < N; i++) ans -= points[i - 1][1] * points[i][0];
ans -= points[N - 1][1] * points[0][0];

ans = Math.abs(ans) * 0.5;

console.log(ans.toFixed(1));
