const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [R, C, T] = inp[0];

const room = inp.slice(1);

let airPurifiorLoc = 0;
for (let i = 0; i < R; i++) {
  if (room[i][0] === -1) {
    airPurifiorLoc = i;
    break;
  }
}

const dirs = [
  [-1, 0],
  [0, 1],
  [1, 0],
  [0, -1],
];

for (let t = 0; t < T; t++) {
  const nxtRoom = Array.from({ length: R }, (_, i) =>
    Array.from({ length: C }, (_, j) => room[i][j])
  );

  //미세먼지 확산
  for (let i = 0; i < R; i++) {
    for (let j = 0; j < C; j++) {
      if (room[i][j] <= 0) continue;
      const curDirt = room[i][j];
      for (let d = 0; d < 4; d++) {
        const [nxtI, nxtJ] = [i + dirs[d][0], j + dirs[d][1]];
        if (R <= nxtI || nxtI < 0 || C <= nxtJ || nxtJ < 0) continue;
        if (room[nxtI][nxtJ] < 0) continue;
        nxtRoom[nxtI][nxtJ] += parseInt(curDirt / 5);
        nxtRoom[i][j] -= parseInt(curDirt / 5);
      }
    }
  }

  //공기청정기 순환
  for (let i = airPurifiorLoc - 1; i > 0; i--) nxtRoom[i][0] = nxtRoom[i - 1][0];
  for (let j = 0; j < C; j++) nxtRoom[0][j] = nxtRoom[0][j + 1];
  for (let i = 0; i < airPurifiorLoc; i++) nxtRoom[i][C - 1] = nxtRoom[i + 1][C - 1];
  for (let j = C - 1; j > 1; j--) nxtRoom[airPurifiorLoc][j] = nxtRoom[airPurifiorLoc][j - 1];
  nxtRoom[airPurifiorLoc][1] = 0;

  for (let i = airPurifiorLoc + 2; i < R - 1; i++) nxtRoom[i][0] = nxtRoom[i + 1][0];
  for (let j = 0; j < C; j++) nxtRoom[R - 1][j] = nxtRoom[R - 1][j + 1];
  for (let i = R - 1; i > airPurifiorLoc + 1; i--) nxtRoom[i][C - 1] = nxtRoom[i - 1][C - 1];
  for (let j = C - 1; j > 1; j--)
    nxtRoom[airPurifiorLoc + 1][j] = nxtRoom[airPurifiorLoc + 1][j - 1];
  nxtRoom[airPurifiorLoc + 1][1] = 0;

  for (let i = 0; i < R; i++) for (let j = 0; j < C; j++) room[i][j] = nxtRoom[i][j];
}

let ans = 0;
for (let i = 0; i < R; i++) {
  for (let j = 0; j < C; j++) {
    if (room[i][j] <= 0) continue;
    ans += room[i][j];
  }
}

console.log(ans);
