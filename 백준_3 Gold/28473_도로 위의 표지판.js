const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));
const [N, M] = inp[0];

const roads = inp.slice(1);

roads.sort((a, b) => {
  if (a[2] == b[2]) return a[3] - b[3];
  return a[2] - b[2];
});

const groupOf = Array.from({ length: N + 1 }, (v, i) => i);

function getGroupOf(node) {
  if (groupOf[groupOf[node]] != groupOf[node]) groupOf[node] = getGroupOf(groupOf[node]);
  return groupOf[node];
}

function setGroupOf(node1, node2) {
  const node1Group = getGroupOf(node1);
  const node2Group = getGroupOf(node2);

  if (node1Group < node2Group) groupOf[node2Group] = node1Group;
  else groupOf[node1Group] = node2Group;
}

const ansSet = [];
let ansWeight = 0;

for (let i in roads) {
  if (getGroupOf(roads[i][0]) == getGroupOf(roads[i][1])) continue;
  setGroupOf(roads[i][0], roads[i][1]);

  ansSet.push(roads[i][2]);
  ansWeight += roads[i][3];
}

if (ansSet.length != N - 1) {
  console.log(-1);
} else {
  ansSet.sort();
  console.log(`${ansSet.join("")} ${ansWeight}`);
}
