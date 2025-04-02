const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const S = Array.from(inp[0]).map((v) => v.charCodeAt(0) - "a".charCodeAt(0));
const T = Array.from(inp[1]).map((v) => v.charCodeAt(0) - "a".charCodeAt(0));

const nxtLoc = Array.from({ length: T.length + 1 }, () => Array.from({ length: 26 }, () => 0));
for (let i = T.length - 1; i >= 0; i--) {
  for (let j = 0; j < 26; j++) nxtLoc[i][j] = nxtLoc[i + 1][j];
  nxtLoc[i][T[i]] = i + 1;
}

let ans = 1;
let curTIdx = 0;
for (let i = 0; i < S.length; i++) {
  if (nxtLoc[curTIdx][S[i]] === 0) {
    ans++;
    curTIdx = 0;
  }

  if (nxtLoc[curTIdx][S[i]] === 0) {
    ans = -1;
    break;
  }
  curTIdx = nxtLoc[curTIdx][S[i]];
}

console.log(ans);
