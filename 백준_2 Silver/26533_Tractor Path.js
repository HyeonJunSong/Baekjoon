const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const n = parseInt(inp[0]);
const board = inp.slice(1);

const s = [0];

const visited = Array.from({ length: n }, () => Array.from({ length: n }, () => false));
while (s.length > 0) {
  const cur = s.pop();
  const [I, J] = [parseInt(cur / n), cur % n];

  if (I === n - 1 && J === n - 1) {
    console.log("Yes");
    process.exit(0);
  }

  if (visited[I][J]) continue;
  visited[I][J] = true;

  if (I + 1 < n && board[I + 1][J] !== "x") s.push((I + 1) * n + J);
  if (J + 1 < n && board[I][J + 1] !== "x") s.push(I * n + J + 1);
}

console.log("No");
