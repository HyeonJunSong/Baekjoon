const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];
const board = inp.slice(1, N + 1);
const ansBoard = Array.from({ length: N }, () => Array.from({ length: M }, () => Infinity));

const dir = [
  [-1, -1],
  [-1, 0],
  [-1, 1],
  [0, 1],
  [1, 1],
  [1, 0],
  [1, -1],
  [0, -1],
];

for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (board[i][j] === 0) continue;
    const queue = Array.from({ length: N * M }, () => 0);
    let f = 0;
    let r = 1;
    queue[f] = i * M + j;
    const visited = Array.from({ length: N }, () => Array.from({ length: M }, () => false));
    visited[i][j] = true;
    ansBoard[i][j] = 0;

    while (f < r) {
      const cur = queue[f++];
      const [curI, curJ] = [parseInt(cur / M), cur % M];

      for (let d = 0; d < 8; d++) {
        const [nxtI, nxtJ] = [curI + dir[d][0], curJ + dir[d][1]];
        if (0 > nxtI || nxtI >= N || 0 > nxtJ || nxtJ >= M) continue;
        if (visited[nxtI][nxtJ]) continue;
        visited[nxtI][nxtJ] = true;
        ansBoard[nxtI][nxtJ] = Math.min(ansBoard[nxtI][nxtJ], ansBoard[curI][curJ] + 1);
        queue[r++] = nxtI * M + nxtJ;
      }
    }
  }
}

console.log(
  ansBoard.reduce(
    (accum, v) =>
      Math.max(
        accum,
        v.reduce((accum, v) => Math.max(accum, v), 0)
      ),
    0
  )
);
