const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const [N, M] = inp[0].split(" ").map((v) => parseInt(v));

const board = inp.slice(1).map((v) =>
  v.split("").map((v) => {
    if (v == "R" || v == "B") return ".";
    else return v;
  })
);

let rCoor = [0, 0];
let bCoor = [0, 0];

for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (inp[1 + i][j] == "R") rCoor = [i, j];
    else if (inp[1 + i][j] == "B") bCoor = [i, j];
  }
}

const dir = [
  [-1, 0],
  [1, 0],
  [0, -1],
  [0, 1],
];

function getMinMove(rLoc, bLoc, cnt) {
  if (cnt >= 10) return 11;

  const rCoor = [parseInt(rLoc / M), rLoc % M];
  const bCoor = [parseInt(bLoc / M), bLoc % M];

  let ans = 11;

  for (let d = 0; d < 4; d++) {
    const nextRCoor = [...rCoor];
    const nextBCoor = [...bCoor];

    if (rCoor[0] * dir[d][0] + rCoor[1] * dir[d][1] > bCoor[0] * dir[d][0] + bCoor[1] * dir[d][1]) {
      while (board[nextRCoor[0] + dir[d][0]][nextRCoor[1] + dir[d][1]] != "#") {
        if (board[nextRCoor[0] + dir[d][0]][nextRCoor[1] + dir[d][1]] == "O") {
          nextRCoor[0] = -1;
          break;
        }
        nextRCoor[0] += dir[d][0];
        nextRCoor[1] += dir[d][1];
      }

      while (
        board[nextBCoor[0] + dir[d][0]][nextBCoor[1] + dir[d][1]] != "#" &&
        !(nextRCoor[0] == nextBCoor[0] + dir[d][0] && nextRCoor[1] == nextBCoor[1] + dir[d][1])
      ) {
        if (board[nextBCoor[0] + dir[d][0]][nextBCoor[1] + dir[d][1]] == "O") {
          nextBCoor[0] = -1;
          break;
        }
        nextBCoor[0] += dir[d][0];
        nextBCoor[1] += dir[d][1];
      }
    } else {
      while (board[nextBCoor[0] + dir[d][0]][nextBCoor[1] + dir[d][1]] != "#") {
        if (board[nextBCoor[0] + dir[d][0]][nextBCoor[1] + dir[d][1]] == "O") {
          nextBCoor[0] = -1;
          break;
        }
        nextBCoor[0] += dir[d][0];
        nextBCoor[1] += dir[d][1];
      }

      while (
        board[nextRCoor[0] + dir[d][0]][nextRCoor[1] + dir[d][1]] != "#" &&
        !(nextRCoor[0] + dir[d][0] == nextBCoor[0] && nextRCoor[1] + dir[d][1] == nextBCoor[1])
      ) {
        if (board[nextRCoor[0] + dir[d][0]][nextRCoor[1] + dir[d][1]] == "O") {
          nextRCoor[0] = -1;
          break;
        }
        nextRCoor[0] += dir[d][0];
        nextRCoor[1] += dir[d][1];
      }
    }

    if (nextBCoor[0] != -1 && nextRCoor[0] != -1) {
      ans = Math.min(
        ans,
        getMinMove(nextRCoor[0] * M + nextRCoor[1], nextBCoor[0] * M + nextBCoor[1], cnt + 1)
      );
    } else if (nextBCoor[0] != -1) {
      ans = Math.min(ans, cnt + 1);
    }
  }

  return ans;
}

const ans = getMinMove(rCoor[0] * M + rCoor[1], bCoor[0] * M + bCoor[1], 0);
console.log(ans > 10 ? -1 : ans);
