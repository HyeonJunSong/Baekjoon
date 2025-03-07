const fs = require("fs");
const N = parseInt(fs.readFileSync("/dev/stdin").toString());

const memo = Array.from({ length: N + 1 }, () => Array.from({ length: 30000 }, () => -1));

function getExpectedValue(k, tries) {
  if (k === 0) return tries;
  if (tries === 30000) return 0;

  if (memo[k][tries] !== -1) return memo[k][tries];
  let ans = 0;
  ans += (k / N) * getExpectedValue(k - 1, tries + 1);
  ans += ((N - k) / N) * getExpectedValue(k, tries + 1);

  memo[k][tries] = ans;
  return ans;
}

console.log(getExpectedValue(N, 0));
