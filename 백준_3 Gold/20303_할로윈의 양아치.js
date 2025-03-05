const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M, K] = inp[0];
const candies = [0, ...inp[1]];
const graph = Array.from({ length: N + 1 }, () => []);
for (let i = 0; i < M; i++) {
  graph[inp[2 + i][0]].push(inp[2 + i][1]);
  graph[inp[2 + i][1]].push(inp[2 + i][0]);
}

const visited = Array.from({ length: N + 1 }, () => false);

const candiesOfGroup = [];

for (let i = 1; i <= N; i++) {
  if (visited[i]) continue;
  visited[i] = true;
  const stack = [i];

  let curGroupCandyCnt = 0;
  let curGroupChildrenCnt = 0;

  while (stack.length > 0) {
    const cur = stack.pop();
    curGroupChildrenCnt++;
    curGroupCandyCnt += candies[cur];

    for (let j = 0; j < graph[cur].length; j++) {
      if (visited[graph[cur][j]]) continue;
      visited[graph[cur][j]] = true;
      stack.push(graph[cur][j]);
    }
  }

  candiesOfGroup.push([curGroupCandyCnt, curGroupChildrenCnt]);
}

const dp = Array.from({ length: K }, () => 0);

for (let i = 0; i < candiesOfGroup.length; i++) {
  for (let k = K - 1; k >= candiesOfGroup[i][1]; k--) {
    dp[k] = Math.max(dp[k], dp[k - candiesOfGroup[i][1]] + candiesOfGroup[i][0]);
  }
}

let ans = 0;
for (let k = 0; k < K; k++) ans = Math.max(ans, dp[k]);
console.log(ans);
