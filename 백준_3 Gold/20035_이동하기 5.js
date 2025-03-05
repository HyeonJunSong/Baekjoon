const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];
const A = inp[1];
const B = inp[2];

const maxRowVal = A.reduce((accum, cur) => Math.max(accum, cur), -Infinity);

const firstMaxRowIdx = A.reduce((accum, cur, idx) => {
  if (cur !== maxRowVal) return accum;
  if (accum !== -1) return accum;
  return idx;
}, -1);
const lastMaxRowIdx = A.reduce((accum, cur, idx) => {
  if (cur !== maxRowVal) return accum;
  return idx;
}, -1);

const maxColVal = B.reduce((accum, cur) => Math.max(accum, cur), -Infinity);

let ans = 0;
ans += 10 ** 9 * A.reduce((accum, val) => accum + val, 0);
ans += 10 ** 9 * maxRowVal * (M - 1);

if (firstMaxRowIdx == lastMaxRowIdx) {
  ans += B.reduce((accum, val) => accum + val, 0);
  ans += B[0] * firstMaxRowIdx;
  ans += B[B.length - 1] * (N - firstMaxRowIdx - 1);
} else {
  ans += B.reduce((accum, val) => accum + val, 0);
  ans += B[0] * firstMaxRowIdx;
  ans += maxColVal * (lastMaxRowIdx - firstMaxRowIdx);
  ans += B[B.length - 1] * (N - lastMaxRowIdx - 1);
}

console.log(ans);
