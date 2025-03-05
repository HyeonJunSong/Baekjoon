const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const N = parseInt(inp[0]);
const firstLine = inp[1];

const ans = [Array.from({ length: N }, () => "."), [...firstLine]];
for (let i = 2; i <= N; i++) {
  const newLine = [...ans[i - 1]];
  //지금 라인에서 누를애들 다 누르기
  for (let j = 0; j < N; j++) {
    if (ans[i - 1][j] === ".") continue;
    if (j > 0) newLine[j - 1] = newLine[j - 1] === "." ? "#" : ".";
    newLine[j] = newLine[j] === "." ? "#" : ".";
    if (j < N - 1) newLine[j + 1] = newLine[j + 1] === "." ? "#" : ".";
  }

  //윗라인에서 눌린거 누르기
  for (let j = 0; j < N; j++) {
    if (ans[i - 2][j] === ".") continue;
    newLine[j] = newLine[j] === "." ? "#" : ".";
  }

  ans.push(newLine);
}

for (let i = 1; i <= N; i++) console.log(ans[i].join(""));
