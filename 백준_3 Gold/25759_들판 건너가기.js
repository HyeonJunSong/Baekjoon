const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));
const [N] = inp[0];
const A = inp[1];

const memo = Array.from({ length: N + 1 }, () => Array.from({ length: 101 }, () => -1));

function getAns(idx, prvVal) {
  if (idx === N) return 0;

  if (memo[idx][prvVal] !== -1) return memo[idx][prvVal];

  let ans = 0;
  ans = Math.max(ans, getAns(idx + 1, prvVal));
  ans = Math.max(
    ans,
    getAns(idx + 1, A[idx]) + (prvVal === 0 ? 0 : Math.abs(prvVal - A[idx]) ** 2)
  );

  memo[idx][prvVal] = ans;
  return ans;
}

console.log(getAns(0, 0));
