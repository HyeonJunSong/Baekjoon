const { readFileSync } = require("fs");

const inp = readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const arr = inp[1];

const memo = Array.from({ length: N }, () => Array.from({ length: N }, () => -1));

function getAns(i, j) {
  const curDate = N - (j - i + 1) + 1;

  if (curDate === N) return arr[i] * curDate;

  if (memo[i][j] !== -1) return memo[i][j];

  let ans = 0;

  ans = Math.max(ans, getAns(i + 1, j) + arr[i] * curDate);
  ans = Math.max(ans, getAns(i, j - 1) + arr[j] * curDate);

  memo[i][j] = ans;

  return ans;
}

console.log(getAns(0, N - 1));
