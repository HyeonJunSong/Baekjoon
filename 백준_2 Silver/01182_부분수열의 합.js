const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => +v));

const [N, S] = inp[0];
const arr = inp[1];

let ans = 0;
function rec(idx, curSum) {
  if (idx == N) {
    ans += curSum === S ? 1 : 0;
    return;
  }

  rec(idx + 1, curSum);
  rec(idx + 1, curSum + arr[idx]);
}

rec(0, 0);
console.log(S === 0 ? ans - 1 : ans);
