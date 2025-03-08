const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().replace("\n", "");

dirMap = {
  D: [1, 0],
  R: [0, 1],
  U: [-1, 0],
  L: [0, -1],
};

const visited = Array.from({ length: 3 }, () => Array.from({ length: 3 }, () => false));

function getPossibleNums(i, j, idx) {
  if (visited[i][j]) return 0;
  if (idx === inp.length) return 1;

  const [nxtI, nxtJ] = [i + dirMap[inp[idx]][0], j + dirMap[inp[idx]][1]];

  if (0 > nxtI || nxtI >= 3 || 0 > nxtJ || nxtJ >= 3) return 0;

  visited[i][j] = true;
  const ans = getPossibleNums(nxtI, nxtJ, idx) + getPossibleNums(nxtI, nxtJ, idx + 1);
  visited[i][j] = false;
  return ans;
}

let ans = 0;
for (let i = 0; i < 3; i++) for (let j = 0; j < 3; j++) ans += getPossibleNums(i, j, 0);
console.log(ans);
