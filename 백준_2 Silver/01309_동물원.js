const fs = require("fs");
const n = parseInt(fs.readFileSync("/dev/stdin").toString());

const dp = Array.from({ length: n }, () => Array.from({ length: 3 }, () => 0));
for (let i = 0; i < 3; i++) dp[0][i] = 1;

const DIV = 9901;

for (let i = 1; i < n; i++) {
  dp[i][0] += (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % DIV;
  dp[i][1] += (dp[i - 1][0] + dp[i - 1][2]) % DIV;
  dp[i][2] += (dp[i - 1][0] + dp[i - 1][1]) % DIV;
}

console.log((dp[n - 1][0] + dp[n - 1][1] + dp[n - 1][2]) % DIV);
