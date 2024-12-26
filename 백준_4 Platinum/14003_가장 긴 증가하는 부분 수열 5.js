const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const N = parseInt(inp[0]);
const A = inp[1].split(" ").map((v) => parseInt(v));

const prvIdx = Array.from({ length: N }, () => -1);
const endIdxOfLength = [];

for (let i = 0; i < N; i++) {
  let st = 0;
  let ed = endIdxOfLength.length - 1;
  while (st <= ed) {
    const mid = parseInt((st + ed) / 2);

    if (A[endIdxOfLength[mid]] < A[i]) st = mid + 1;
    else ed = mid - 1;
  }

  prvIdx[i] = endIdxOfLength[ed] ?? -1;
  if (st == endIdxOfLength.lastIndexOf) endIdxOfLength.push(i);
  else endIdxOfLength[st] = i;
}

let curIdx = endIdxOfLength[endIdxOfLength.length - 1];
const ansList = [];
while (curIdx !== -1) {
  ansList.push(A[curIdx]);
  curIdx = prvIdx[curIdx];
}

console.log(ansList.length);
console.log(ansList.reverse().join(" "));
