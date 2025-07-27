const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, H] = inp[0];
const obstacles = Array.from({ length: N }, (v, i) => inp[i + 1][0]);

const arr = Array.from({ length: H + 1 }, () => 0);
for (let i = 0; i < N; i += 2) {
  arr[0]++;
  arr[obstacles[i]]--;
}
for (let i = 1; i < N; i += 2) {
  arr[H - obstacles[i]]++;
  arr[H]--;
}

for (let i = 1; i <= H; i++) arr[i] += arr[i - 1];

let ansLen = Infinity;
let ansCnt = 0;
for (let i = 0; i < H; i++) {
  if (ansLen > arr[i]) {
    ansLen = arr[i];
    ansCnt = 1;
  } else if (ansLen == arr[i]) ansCnt++;
}

console.log(ansLen, ansCnt);
