const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const cards = inp[1];

const memo = Array.from({ length: N }, () => Array.from({ length: N }, () => -1));
const maxBetween = Array.from({ length: N }, () => Array.from({ length: N }, () => -1));
for (let i = 0; i < N; i++) {
  maxBetween[i][i] = cards[i];
  for (let j = i + 1; j < N; j++) maxBetween[i][j] = Math.max(maxBetween[i][j - 1], cards[j]);
}

function getAns(st, ed) {
  if (st === ed) return 0;
  if (memo[st][ed] !== -1) return memo[st][ed];

  let ans = Infinity;

  for (let i = st; i < ed; i++)
    ans = Math.min(
      ans,
      getAns(st, i) + getAns(i + 1, ed) + maxBetween[st][i] + maxBetween[i + 1][ed]
    );

  memo[st][ed] = ans;
  return ans;
}

console.log(getAns(0, N - 1));
