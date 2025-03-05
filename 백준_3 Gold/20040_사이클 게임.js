const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [n, m] = inp[0];

const groupOf = Array.from({ length: n }, (v, i) => i);
function getGroupOf(idx) {
  if (groupOf[idx] !== groupOf[groupOf[idx]]) groupOf[idx] = getGroupOf(groupOf[idx]);
  return groupOf[idx];
}
function setGroupOf(idx1, idx2) {
  const g1 = getGroupOf(idx1);
  const g2 = getGroupOf(idx2);

  if (g1 < g2) groupOf[g2] = g1;
  else groupOf[g1] = g2;
}

let ans = 0;
for (let i = 1; i <= m; i++) {
  if (getGroupOf(inp[i][0]) == getGroupOf(inp[i][1])) {
    ans = i;
    break;
  }

  setGroupOf(inp[i][0], inp[i][1]);
}

console.log(ans);
