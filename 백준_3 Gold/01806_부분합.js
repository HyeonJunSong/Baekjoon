const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, S] = inp[0];
const arr = inp[1];
for (let i = 1; i < N; i++) arr[i] += arr[i - 1];

let ans = 987654321;
for (let i = 0; i < N; i++) {
  if (arr[i] < S) continue;

  let st = 0;
  let ed = i - 1;
  const target = arr[i] - S;

  while (st <= ed) {
    const mid = (st + ed) >> 1;

    if (arr[mid] <= target) st = mid + 1;
    else ed = mid - 1;
  }

  ans = Math.min(ans, i - ed);
}

console.log(ans === 987654321 ? 0 : ans);
