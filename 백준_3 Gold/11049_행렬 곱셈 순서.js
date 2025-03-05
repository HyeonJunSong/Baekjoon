const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const matrixes = inp.slice(1);

const memo = Array.from({ length: N }, () => Array.from({ length: N }, () => -1));

function getMinMatrixMult(st, ed) {
  //메모이제이션 꺼내기
  if (memo[st][ed] !== -1) return memo[st][ed];

  //기저
  if (st == ed) return 0;

  //실행부
  let ans = Infinity;
  for (let i = st; i < ed; i++) {
    let curAns = 0;
    curAns += getMinMatrixMult(st, i);
    curAns += getMinMatrixMult(i + 1, ed);
    curAns += matrixes[st][0] * matrixes[i][1] * matrixes[ed][1];

    ans = Math.min(ans, curAns);
  }

  //메모이제이션 쓰기
  memo[st][ed] = ans;

  //출력
  return ans;
}

console.log(getMinMatrixMult(0, N - 1));
