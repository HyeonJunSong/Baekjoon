const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];

const m = inp[1];
const c = inp[2];

const dp = Array.from({ length: 10001 }, () => 0);
for (let i = 0; i < N; i++)
  for (let j = 10000 - c[i]; j >= 0; j--) dp[j + c[i]] = Math.max(dp[j + c[i]], dp[j] + m[i]);

let st = 0;
let ed = 10000;

while (st <= ed) {
  const mid = (st + ed) >> 1;
  if (dp[mid] < M) st = mid + 1;
  else ed = mid - 1;
}

console.log(st);
