const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));
const [N, M, X, Y] = inp[0];
const A = inp[1];
const edges = inp.slice(2, 2 + M);
const B = inp[2 + M];

const graph = Array.from({ length: N + 1 }, () => []);
edges.forEach((v) => {
  graph[v[0]].push(v[1]);
  graph[v[1]].push(v[0]);
});

const possibleCnt = Array.from({ length: N + 1 }, () => Infinity);

const queue = [];
let f = 0;
let r = 0;
B.forEach((v) => {
  possibleCnt[v] = 0;
  queue[r++] = v;
});

while (f < r) {
  const cur = queue[f++];
  graph[cur].forEach((v) => {
    if (possibleCnt[v] <= possibleCnt[cur] + 1) return;
    possibleCnt[v] = possibleCnt[cur] + 1;
    queue[r++] = v;
  });
}

for (let i = 0; i < N; i++) {
  if (possibleCnt[i + 1] !== Infinity) continue;
  if (A[i] === 0) {
    possibleCnt[i + 1] = 0;
    continue;
  }
  console.log(-1);
  process.exit(0);
}

const ans = Array.from({ length: N }, (_, v) => BigInt(possibleCnt[v + 1]) * BigInt(A[v]))
  .sort((a, b) => parseInt(b - a))
  .slice(0, X)
  .reduce((accum, cur) => accum + cur, 0n);
console.log(ans.toString());
