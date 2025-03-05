const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [N, M] = inp[0].split(" ").map((v) => parseInt(v));
const board = inp.slice(1);

const groupOf = Array.from({ length: N }, () => Array.from({ length: M }, () => -1));
const moveableOfGroup = [];

const dir = [
  [-1, 0],
  [1, 0],
  [0, -1],
  [0, 1],
];

for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (board[i][j] === "1") continue;
    if (groupOf[i][j] !== -1) continue;

    let curMovable = 0;
    const curGroup = moveableOfGroup.length;
    groupOf[i][j] = curGroup;

    const s = [[i, j]];

    while (s.length > 0) {
      const cur = s[s.length - 1];
      s.pop();
      curMovable += 1;

      for (let d = 0; d < 4; d++) {
        if (
          0 <= cur[0] + dir[d][0] &&
          cur[0] + dir[d][0] < N &&
          0 <= cur[1] + dir[d][1] &&
          cur[1] + dir[d][1] < M &&
          board[cur[0] + dir[d][0]][cur[1] + dir[d][1]] === "0" &&
          groupOf[cur[0] + dir[d][0]][cur[1] + dir[d][1]] === -1
        ) {
          groupOf[cur[0] + dir[d][0]][cur[1] + dir[d][1]] = curGroup;
          s.push([cur[0] + dir[d][0], cur[1] + dir[d][1]]);
        }
      }
    }

    moveableOfGroup.push(curMovable);
  }
}

const ans = Array.from({ length: N }, () => Array.from({ length: M }, () => 0));
for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (board[i][j] === "0") continue;
    const dirSet = new Set();
    for (let d = 0; d < 4; d++) {
      if (
        0 <= i + dir[d][0] &&
        i + dir[d][0] < N &&
        0 <= j + dir[d][1] &&
        j + dir[d][1] < M &&
        board[i + dir[d][0]][j + dir[d][1]] === "0"
      )
        dirSet.add(groupOf[i + dir[d][0]][j + dir[d][1]]);
    }

    ans[i][j]++;
    dirSet.forEach((v) => (ans[i][j] += moveableOfGroup[v]));
    ans[i][j] %= 10;
  }
}

for (let i = 0; i < N; i++) console.log(ans[i].join(""));
