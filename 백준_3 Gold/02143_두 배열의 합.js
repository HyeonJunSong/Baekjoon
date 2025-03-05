const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => +v));

const [T] = inp[0];
const [n] = inp[1];
const A = [0, ...inp[2]];
const [m] = inp[3];
const B = [0, ...inp[4]];

const bNumMap = new Map();

for (let i = 1; i <= m; i++) B[i] += B[i - 1];
for (let i = 1; i <= n; i++) A[i] += A[i - 1];

for (let i = 0; i < m; i++)
  for (let j = i + 1; j <= m; j++) bNumMap.set(B[j] - B[i], (bNumMap.get(B[j] - B[i]) ?? 0) + 1);

let ans = 0;
for (let i = 0; i < n; i++)
  for (let j = i + 1; j <= n; j++) ans += bNumMap.get(T - (A[j] - A[i])) ?? 0;

console.log(ans);
