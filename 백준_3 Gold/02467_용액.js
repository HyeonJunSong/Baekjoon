const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const arr = inp[1];

let ansVal = arr[N - 2] + arr[N - 1];
const ansPair = [arr[N - 2], arr[N - 1]];

for (let i = 0; i < N - 2; i++) {
  const target = -arr[i];
  let st = i + 2;
  let ed = N - 2;

  while (st <= ed) {
    const mid = parseInt((st + ed) / 2);
    if (arr[mid] < target) st = mid + 1;
    else ed = mid - 1;
  }

  if (ansVal > Math.abs(arr[st] + arr[i])) {
    ansVal = Math.abs(arr[st] + arr[i]);
    ansPair[0] = arr[i];
    ansPair[1] = arr[st];
  }

  if (ansVal > Math.abs(arr[ed] + arr[i])) {
    ansVal = Math.abs(arr[ed] + arr[i]);
    ansPair[0] = arr[i];
    ansPair[1] = arr[ed];
  }
}
console.log(`${ansPair[0]} ${ansPair[1]}`);
