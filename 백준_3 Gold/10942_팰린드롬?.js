const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => +v));

const [N] = inp[0];
const arr = inp[1];
const [M] = inp[2];

const dp = Array.from({ length: N }, () => Array.from({ length: N }, () => 0));
for (let i = 0; i < N; i++) dp[i][i] = 1;
for (let i = 0; i < N - 1; i++) if (arr[i] == arr[i + 1]) dp[i][i + 1] = 1;

for (let j = 2; j < N; j++) {
  for (let i = 0; i < N - j; i++) {
    if (dp[i + 1][i + j - 1] && arr[i] === arr[i + j]) dp[i][i + j] = 1;
  }
}

const ans = Array.from({ length: M }, () => 0);
for (let i = 0; i < M; i++) ans[i] = dp[inp[3 + i][0] - 1][inp[3 + i][1] - 1];
console.log(ans.join("\n"));
