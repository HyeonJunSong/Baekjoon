const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const board = inp.slice(1);

let ans = Infinity;

const nPow = 2 ** N;

function sumList(list) {
  let s = 0;
  list.forEach((v) => (s += v));
  return s;
}

for (let flipR = 0; flipR < nPow; flipR++) {
  for (let flipC = 0; flipC < nPow; flipC++) {
    const flipRList = Array.from({ length: N }, () => 0);
    const flipCList = Array.from({ length: N }, () => 0);

    let bit = 1;
    for (let k = 0; k < N; k++, bit <<= 1) {
      if (bit & flipR) flipRList[k] = 1;
      if (bit & flipC) flipCList[k] = 1;
    }

    let bCnt = 0;
    for (let i = 0; i < N; i++) {
      for (let j = 0; j < N; j++) {
        if ((flipRList[i] ^ flipCList[j]) === 1 && board[i][j] === 0) bCnt++;
        else if ((flipRList[i] ^ flipCList[j]) === 0 && board[i][j] === 1) bCnt++;
      }
    }

    ans = Math.min(ans, Math.min(bCnt, N * N - bCnt) + sumList(flipRList) + sumList(flipCList));
  }
}

console.log(ans);
