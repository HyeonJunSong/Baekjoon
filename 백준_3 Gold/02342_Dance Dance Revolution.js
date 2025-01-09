const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const command = inp[0];

const energy = [
  [0, 2, 2, 2, 2],
  [0, 1, 3, 4, 3],
  [0, 3, 1, 3, 4],
  [0, 4, 3, 1, 3],
  [0, 3, 4, 3, 1],
];

const memo = Array.from({ length: command.length - 1 }, () =>
  Array.from({ length: 5 }, () => Array.from({ length: 5 }, () => -1))
);

function dp(idx, left, right) {
  if (idx == command.length - 1) return 0;

  if (memo[idx][left][right] !== -1) return memo[idx][left][right];

  let ans = 987654321;
  if (right != command[idx])
    ans = Math.min(ans, dp(idx + 1, command[idx], right) + energy[left][command[idx]]);
  if (left != command[idx])
    ans = Math.min(ans, dp(idx + 1, left, command[idx]) + energy[right][command[idx]]);

  memo[idx][left][right] = ans;
  return ans;
}

console.log(dp(0, 0, 0));
