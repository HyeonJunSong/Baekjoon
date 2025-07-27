const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => parseInt(v));

const numOfWeight = Array.from({ length: 20001 }, () => 0);
for (let i = 1; i <= inp[0]; i++) numOfWeight[inp[i]]++;

const totSum = numOfWeight.reduce((prv, cur, idx) => prv + cur * idx, 0);
let curSum = 0;

for (let i = 1; i <= 20000; i++) {
  if (curSum * 2 === totSum - numOfWeight[i] * i) {
    console.log(i);
    break;
  }
  curSum += numOfWeight[i] * i;
}
