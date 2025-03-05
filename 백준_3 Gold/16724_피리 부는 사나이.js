const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const [N, M] = inp[0].split(" ").map((v) => parseInt(v));
const board = inp.splice(1);

let ans = 0;
const visited = Array.from({ length: N }, () => Array.from({ length: M }, () => 0));

const dirMap = {
  U: [-1, 0],
  D: [1, 0],
  L: [0, -1],
  R: [0, 1],
};

for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (visited[i][j] == 2) continue;

    const stack = [[i, j]];
    while (true) {
      const cur = stack[stack.length - 1];
      if (visited[cur[0]][cur[1]] == 0) {
        visited[cur[0]][cur[1]] = 1;
        stack.push([
          cur[0] + dirMap[board[cur[0]][cur[1]]][0],
          cur[1] + dirMap[board[cur[0]][cur[1]]][1],
        ]);
        continue;
      }
      if (visited[cur[0]][cur[1]] == 1) ans++;
      for (let k = 0; k < stack.length; k++) visited[stack[k][0]][stack[k][1]] = 2;
      break;
    }
  }
}

console.log(ans);
