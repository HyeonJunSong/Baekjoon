const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [N, M] = inp[0].split(" ").map((v) => parseInt(v));
const board = inp.slice(1, 1 + N);

const dp = Array.from({ length: M }, () => Array.from({ length: M }, () => 0));

let ans = 0;
for (let i = N - 1; i >= 0; i--) {
  for (let j = 0; j < M; j++) {
    for (let k = 0; k < M - j; k++) {
      if (k > 0 && dp[j][k - 1] === 0) {
        dp[j][k] = 0;
        continue;
      }
      if (board[i][j + k] === "1") {
        dp[j][k] = 0;
        continue;
      }

      dp[j][k]++;

      ans = Math.max(ans, dp[j][k] * (k + 1));
    }
  }
}

console.log(ans);
