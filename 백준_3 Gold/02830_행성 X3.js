const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => parseInt(v));

const N = inp[0];

const names = inp.slice(1, 1 + N);

const bitCnt = Math.ceil(Math.log2(names.reduce((accum, cur) => Math.max(accum, cur), 0)));

const bitCnt0 = Array.from({ length: bitCnt }, () => 0);
const bitCnt1 = Array.from({ length: bitCnt }, () => 0);

for (let i = 0; i < N; i++) {
  let name = names[i];
  for (let bit = 0; bit < bitCnt; bit++) {
    if (name % 2 === 0) bitCnt0[bit]++;
    else bitCnt1[bit]++;

    name >>= 1;
  }
}

console.log(
  Array.from({ length: bitCnt }, (_, i) => bitCnt0[i] * bitCnt1[i] * (1 << i))
    .reduce((acc, cur) => acc + BigInt(cur), 0n)
    .toString()
    .replace("n", "")
);
