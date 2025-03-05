const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [str1, str2] = inp;

const dp = Array.from({ length: str1.length }, () =>
  Array.from({ length: str2.length }, () => [-1, -1])
);

function LCS(idx1, idx2) {
  if (idx1 == str1.length || idx2 == str2.length) {
    return [0, -1];
  }

  if (dp[idx1][idx2][0] != -1) return dp[idx1][idx2];

  let ansCnt = 0;
  let ansCase = -1; //-1 : 더이상 진행하지 않음 | 0 : 둘 다 옮김 | 1 : idx1만 옮김 | 2 : idx2만 옮김
  let res;

  if (str1[idx1] == str2[idx2]) {
    res = LCS(idx1 + 1, idx2 + 1);
    if (res[0] + 1 > ansCnt) {
      ansCnt = res[0] + 1;
      ansCase = 0;
    }
  }

  res = LCS(idx1 + 1, idx2);
  if (res[0] > ansCnt) {
    ansCnt = res[0];
    ansCase = 1;
  }

  res = LCS(idx1, idx2 + 1);
  if (res[0] + 1 > ansCnt) {
    ansCnt = res[0];
    ansCase = 2;
  }

  dp[idx1][idx2][0] = ansCnt;
  dp[idx1][idx2][1] = ansCase;
  return [ansCnt, ansCase];
}

let ansCnt = LCS(0, 0)[0];
let ansStr = [];

let idx1 = 0;
let idx2 = 0;
while (true) {
  const cur = LCS(idx1, idx2);
  if (cur[1] == -1) break;
  else if (cur[1] == 0) {
    ansStr.push(str1[idx1]);
    idx1++;
    idx2++;
  } else if (cur[1] == 1) idx1++;
  else idx2++;
}

console.log(ansCnt);
console.log(ansStr.join(""));
