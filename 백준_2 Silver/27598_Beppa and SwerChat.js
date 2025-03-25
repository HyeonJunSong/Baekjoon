const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let idx = 0;
let [t] = inp[idx++];

function solve() {
  const [n] = inp[idx++];
  const a = inp[idx++].reverse();
  const b = inp[idx++].reverse();

  let aIdx = 0,
    bIdx = 0;

  while (bIdx < n) {
    while (aIdx < n && a[aIdx] != b[bIdx]) aIdx++;
    if (aIdx == n) break;
    aIdx++;
    bIdx++;
  }
  console.log(n - bIdx);
  return;
}

while (t-- > 0) solve();
