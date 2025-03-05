const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, R, Q] = inp[0];
const tree = Array.from({ length: N + 1 }, () => []);
for (let i = 0; i < N - 1; i++) {
  tree[inp[1 + i][0]].push(inp[1 + i][1]);
  tree[inp[1 + i][1]].push(inp[1 + i][0]);
}

const vertexNumOf = Array.from({ length: N + 1 }, () => 0);
function getVertexNum(cur, prv) {
  let vertexNum = 1;
  for (let i = 0; i < tree[cur].length; i++) {
    if (tree[cur][i] == prv) continue;
    vertexNum += getVertexNum(tree[cur][i], cur);
  }

  vertexNumOf[cur] = vertexNum;
  return vertexNum;
}

getVertexNum(R, R);

for (let i = 0; i < Q; i++) {
  console.log(vertexNumOf[inp[1 + N - 1 + i][0]]);
}
