const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];

const groupOf = Array.from({ length: N + 1 }, (v, i) => i);
function getGroupOf(vertex) {
  if (groupOf[vertex] != groupOf[groupOf[vertex]]) groupOf[vertex] = getGroupOf(groupOf[vertex]);
  return groupOf[vertex];
}
function setGroup(v1, v2) {
  const v1G = getGroupOf(v1);
  const v2G = getGroupOf(v2);

  if (v1G < v2G) groupOf[v2G] = v1G;
  else groupOf[v1G] = v2G;
}

const edges = inp.splice(1).sort((a, b) => a[2] - b[2]);

let ans = 0;
let maxEdge = 0;
for (let i = 0; i < M; i++) {
  if (getGroupOf(edges[i][0]) == getGroupOf(edges[i][1])) continue;
  ans += edges[i][2];
  setGroup(edges[i][0], edges[i][1]);
  maxEdge = Math.max(maxEdge, edges[i][2]);
}

console.log(ans - maxEdge);
