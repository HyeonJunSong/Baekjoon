const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
let inpIdx = 0;

const t = parseInt(inp[inpIdx++]);

const dir = [
  [-1, 0],
  [0, 1],
  [1, 0],
  [0, -1],
];

function testCase() {
  const [h, w] = inp[inpIdx++].split(" ").map((v) => parseInt(v));
  const board = inp.slice(inpIdx, inpIdx + h).map((v) => v.split(""));
  inpIdx += h;
  const keys = inp[inpIdx++].split("");

  const doorCoor = Array.from({ length: 26 }, () => []);
  for (let i = 0; i < h; i++) {
    for (let j = 0; j < w; j++) {
      const curCharCode = board[i][j].charCodeAt();
      if (65 <= curCharCode && curCharCode <= 90) doorCoor[curCharCode - 65].push([i, j]);
    }
  }

  const isOpen = Array.from({ length: 26 }, () => false);
  function openDoor(key) {
    const keyIdx = key.charCodeAt() - 97;
    if (isOpen[keyIdx]) return;
    doorCoor[keyIdx].forEach((v) => (board[v[0]][v[1]] = "."));
    isOpen[keyIdx] = true;
  }

  let ans = 0;
  function grabDoc(i, j) {
    ans++;
    board[i][j] = ".";
  }

  if (keys[0] != "0") keys.forEach(openDoor);

  while (true) {
    let isChanged = false;

    const enterance = [];
    for (let i = 0; i < h; i++) {
      if (board[i][0] == "*" || (65 <= board[i][0].charCodeAt() && board[i][0].charCodeAt() <= 90))
        continue;

      enterance.push([i, 0]);
      if (board[i][0] == ".") continue;
      if (board[i][0] == "$") grabDoc(i, 0);
      else {
        openDoor(board[i][0]);
        board[i][0] = ".";
        isChanged = true;
      }
    }
    for (let i = 0; i < h; i++) {
      if (
        board[i][w - 1] == "*" ||
        (65 <= board[i][w - 1].charCodeAt() && board[i][w - 1].charCodeAt() <= 90)
      )
        continue;

      enterance.push([i, w - 1]);
      if (board[i][w - 1] == ".") continue;
      if (board[i][w - 1] == "$") grabDoc(i, w - 1);
      else {
        openDoor(board[i][w - 1]);
        board[i][w - 1] = ".";
        isChanged = true;
      }
    }
    for (let j = 0; j < w; j++) {
      if (board[0][j] == "*" || (65 <= board[0][j].charCodeAt() && board[0][j].charCodeAt() <= 90))
        continue;

      enterance.push([0, j]);
      if (board[0][j] == ".") continue;
      if (board[0][j] == "$") grabDoc(0, j);
      else {
        openDoor(board[0][j]);
        board[0][j] = ".";
        isChanged = true;
      }
    }
    for (let j = 0; j < w; j++) {
      if (
        board[h - 1][j] == "*" ||
        (65 <= board[h - 1][j].charCodeAt() && board[h - 1][j].charCodeAt() <= 90)
      )
        continue;

      enterance.push([h - 1, j]);
      if (board[h - 1][j] == ".") continue;
      if (board[h - 1][j] == "$") grabDoc(h - 1, j);
      else {
        openDoor(board[h - 1][j]);
        board[h - 1][j] = ".";
        isChanged = true;
      }
    }
    const stack = [...enterance];
    const visited = Array.from({ length: h }, () => Array.from({ length: w }, () => false));
    stack.forEach((v) => (visited[v[0]][v[1]] = true));

    while (stack.length > 0) {
      const [I, J] = stack[stack.length - 1];
      stack.pop();

      for (let d = 0; d < 4; d++) {
        if (!(0 < I + dir[d][0] && I + dir[d][0] < h && 0 < J + dir[d][1] && J + dir[d][1] < w))
          continue;
        if (visited[I + dir[d][0]][J + dir[d][1]]) continue;
        if (
          board[I + dir[d][0]][J + dir[d][1]] == "*" ||
          (65 <= board[I + dir[d][0]][J + dir[d][1]].charCodeAt() &&
            board[I + dir[d][0]][J + dir[d][1]].charCodeAt() <= 90)
        )
          continue;

        stack.push([I + dir[d][0], J + dir[d][1]]);
        visited[I + dir[d][0]][J + dir[d][1]] = true;

        if (board[I + dir[d][0]][J + dir[d][1]] == ".") continue;
        if (board[I + dir[d][0]][J + dir[d][1]] == "$") grabDoc(I + dir[d][0], J + dir[d][1]);
        else {
          if (isOpen[board[I + dir[d][0]][J + dir[d][1]].charCodeAt() - 97]) continue;
          openDoor(board[I + dir[d][0]][J + dir[d][1]]);
          isChanged = true;
        }
      }
    }

    if (!isChanged) break;
  }

  console.log(ans);

  return;
}

for (let i = 0; i < t; i++) testCase();
