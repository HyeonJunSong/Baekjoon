const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split("").map((v) => parseInt(v)));

const numOfRow = Array.from({ length: 9 }, () => Array.from({ length: 10 }, () => false));
const numOfCol = Array.from({ length: 9 }, () => Array.from({ length: 10 }, () => false));
const numOfCell = Array.from({ length: 9 }, () => Array.from({ length: 10 }, () => false));

for (let i = 0; i < 9; i++) {
  for (let j = 0; j < 9; j++) {
    numOfRow[i][inp[i][j]] = true;
    numOfCol[j][inp[i][j]] = true;
    numOfCell[parseInt(i / 3) * 3 + parseInt(j / 3)][inp[i][j]] = true;
  }
}

function getAns(loc) {
  // console.log(loc);
  // for (let i = 0; i < 9; i++) console.log(inp[i].join(""));
  if (loc == 81) {
    for (let i = 0; i < 9; i++) console.log(inp[i].join(""));
    return true;
  }

  const I = parseInt(loc / 9);
  const J = loc % 9;

  if (inp[I][J] != 0) return getAns(loc + 1);

  for (let i = 1; i <= 9; i++) {
    if (numOfRow[I][i]) continue;
    if (numOfCol[J][i]) continue;
    if (numOfCell[parseInt(I / 3) * 3 + parseInt(J / 3)][i]) continue;

    numOfRow[I][i] = true;
    numOfCol[J][i] = true;
    numOfCell[parseInt(I / 3) * 3 + parseInt(J / 3)][i] = true;
    inp[I][J] = i;

    if (getAns(loc + 1)) return true;

    inp[I][J] = 0;
    numOfRow[I][i] = false;
    numOfCol[J][i] = false;
    numOfCell[parseInt(I / 3) * 3 + parseInt(J / 3)][i] = false;
  }

  return false;
}

getAns(0);
