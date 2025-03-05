const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const arr = inp[1].sort((a, b) => a - b);

if (N <= 2) {
  console.log(N);
  process.exit(0);
}

let ans = 2;
for (let i = 0; i < N - 2; i++) {
  for (let j = i + 1; j < N - 1; j++) {
    let curPossible = 0;
    for (let k = j + 1; k < N; k++) {
      if (arr[i] + arr[j] <= arr[k]) break;
      curPossible++;
    }
    ans = Math.max(ans, curPossible + 2);
  }
}

console.log(ans);
