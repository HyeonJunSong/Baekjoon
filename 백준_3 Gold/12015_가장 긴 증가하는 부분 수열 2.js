const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const arr = inp[1];

const frontOf = Array.from({ length: N }, () => -1);
const lastIdxOf = [];

for (let i = 0; i < N; i++) {
  let st = 0;
  let ed = lastIdxOf.length - 1;

  while (st <= ed) {
    const mid = (st + ed) >> 1;

    if (arr[lastIdxOf[mid]] < arr[i]) st = mid + 1;
    else ed = mid - 1;
  }

  if (st == lastIdxOf.length) lastIdxOf.push(i);
  else lastIdxOf[st] = i;

  frontOf[i] = st - 1 < 0 ? -1 : lastIdxOf[st - 1];
}

console.log(lastIdxOf.length);
