const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [V, E] = inp[0];

const groupOf = Array.from({ length: V + 1 }, (v, i) => i);
function getGroup(node) {
  if (groupOf[node] !== groupOf[groupOf[node]]) groupOf[node] = getGroup(groupOf[node]);
  return groupOf[node];
}
function setGroup(node1, node2) {
  const node1G = getGroup(node1);
  const node2G = getGroup(node2);

  if (node1G < node2G) groupOf[node2G] = node1G;
  else groupOf[node1G] = node2G;
}

const edges = inp.slice(1);
edges.sort((a, b) => a[2] - b[2]);

let ans = 0;
for (let i = 0; i < E; i++) {
  if (getGroup(edges[i][0]) === getGroup(edges[i][1])) continue;
  ans += edges[i][2];
  setGroup(edges[i][0], edges[i][1]);
}
console.log(ans);
