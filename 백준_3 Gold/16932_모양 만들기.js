const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];
const board = inp.slice(1);

const dirs = [
  [-1, 0],
  [0, -1],
  [0, 1],
  [1, 0],
];

const groupOf = Array.from({ length: N }, () => Array.from({ length: M }, () => -1));

const sizeof = [];

for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (groupOf[i][j] !== -1) continue;
    if (board[i][j] === 0) continue;

    const s = [[i, j]];
    let curSizeOf = 0;
    while (s.length > 0) {
      const [I, J] = s.pop();
      if (groupOf[I][J] !== -1) continue;
      groupOf[I][J] = sizeof.length;

      curSizeOf++;
      for (let d = 0; d < 4; d++) {
        const [nxtI, nxtJ] = [I + dirs[d][0], J + dirs[d][1]];
        if (0 > nxtI || nxtI >= N || 0 > nxtJ || nxtJ >= M) continue;
        if (board[nxtI][nxtJ] === 0) continue;
        s.push([nxtI, nxtJ]);
      }
    }

    sizeof.push(curSizeOf);
  }
}

let ans = 0;
for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (board[i][j] === 1) continue;
    const curGroup = new Set();
    for (let d = 0; d < 4; d++) {
      const [nxtI, nxtJ] = [i + dirs[d][0], j + dirs[d][1]];
      if (0 > nxtI || nxtI >= N || 0 > nxtJ || nxtJ >= M) continue;
      if (groupOf[nxtI][nxtJ] === -1) continue;
      curGroup.add(groupOf[nxtI][nxtJ]);
    }

    let curAns = 1;
    curGroup.forEach((v) => (curAns += sizeof[v]));
    ans = Math.max(ans, curAns);
  }
}

console.log(ans);
