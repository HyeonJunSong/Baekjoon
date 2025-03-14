const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, K] = inp[0];
const a = inp[1];

let sMax = K - a[0];
let nMax = K + a[0];

let ans = -Infinity;
for (let i = 1; i < N; i++) {
  ans = Math.max(ans, sMax + (-(i + 1) * K + a[i]));
  ans = Math.max(ans, nMax + (-(i + 1) * K - a[i]));

  sMax = Math.max(sMax, (i + 1) * K - a[i]);
  nMax = Math.max(nMax, (i + 1) * K + a[i]);
}

console.log(ans);
