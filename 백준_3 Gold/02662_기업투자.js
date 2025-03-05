const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));
const [N, M] = inp[0];

const investments = Array.from({ length: N + 1 }, () => Array.from({ length: M + 1 }, () => 0));
for (let i = 1; i <= N; i++) for (let j = 0; j <= M; j++) investments[i][j] = inp[i][j];

const memo = Array.from({ length: M }, () => Array.from({ length: N + 1 }, () => [-1, []]));

function getMax(idx, leftCash) {
  if (idx == M - 1) return [investments[leftCash][1 + idx], [leftCash]];

  if (memo[idx][leftCash][0] != -1) return memo[idx][leftCash];

  let ans = 0;
  let ansAmount = [];
  for (let i = 0; i <= leftCash; i++) {
    const nxtMax = getMax(idx + 1, leftCash - i);
    if (ans < nxtMax[0] + investments[i][idx + 1]) {
      ans = nxtMax[0] + investments[i][idx + 1];
      ansAmount = [i, ...nxtMax[1]];
    }
  }

  memo[idx][leftCash][0] = ans;
  memo[idx][leftCash][1] = ansAmount;
  return memo[idx][leftCash];
}

const [amount, way] = getMax(0, N);
console.log(amount);
console.log(way.join(" "));
