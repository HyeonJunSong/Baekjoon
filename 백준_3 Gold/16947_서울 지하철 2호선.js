const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const edges = inp.slice(1);

const graph = Array.from({ length: N + 1 }, () => []);
for (let i = 0; i < N; i++) {
  graph[edges[i][0]].push(edges[i][1]);
  graph[edges[i][1]].push(edges[i][0]);
}

const ifCycle = Array.from({ length: N + 1 }, () => false);

function findCycle(par, cur, visited, stack) {
  if (visited[cur]) {
    let idx = stack.length - 1;
    while (stack[idx] !== cur) ifCycle[stack[idx--]] = true;
    ifCycle[stack[idx]] = true;

    return true;
  }

  visited[cur] = true;
  stack.push(cur);
  for (let i = 0; i < graph[cur].length; i++) {
    if (graph[cur][i] === par) continue;
    if (findCycle(cur, graph[cur][i], visited, stack)) return true;
  }
  stack.pop();
  visited[cur] = false;

  return false;
}
findCycle(
  1,
  1,
  Array.from({ length: N + 1 }, () => false),
  []
);

const distanceOf = Array.from({ length: N + 1 }, () => 0);
function markDistance(par, cur, dis) {
  distanceOf[cur] = dis;
  for (let i = 0; i < graph[cur].length; i++) {
    if (graph[cur][i] === par) continue;
    markDistance(cur, graph[cur][i], dis + 1);
  }
}

for (let i = 1; i <= N; i++) {
  if (!ifCycle[i]) continue;
  for (let j = 0; j < graph[i].length; j++) {
    if (ifCycle[graph[i][j]]) continue;
    markDistance(i, graph[i][j], 1);
  }
}

console.log(distanceOf.slice(1).join(" "));
