const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let idx = 0;
let [T] = inp[idx++];

function getShortestPath(visited, st, cnt, beepers, prv) {
  if (cnt === visited.length) return Math.abs(prv[0] - st[0]) + Math.abs(prv[1] - st[1]);

  let ans = Infinity;
  for (let i = 0; i < visited.length; i++) {
    if (visited[i]) continue;
    visited[i] = true;

    const shortestPath = getShortestPath(visited, st, cnt + 1, beepers, beepers[i]);

    ans = Math.min(
      ans,
      shortestPath + Math.abs(prv[0] - beepers[i][0]) + Math.abs(prv[1] - beepers[i][1])
    );

    visited[i] = false;
  }

  return ans;
}

function solve() {
  idx++;
  const st = inp[idx++];

  const [beeperCnt] = inp[idx++];
  const beepers = inp.slice(idx, idx + beeperCnt);
  idx += beeperCnt;

  console.log(
    `The shortest path has length ${getShortestPath(
      Array.from({ length: beeperCnt }, () => false),
      st,
      0,
      beepers,
      st
    )}`
  );
}

while (T--) solve();
