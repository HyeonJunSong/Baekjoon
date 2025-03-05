const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, K] = inp[0];
const I = inp[1];

const ifPossible = Array.from({ length: 50001 }, () => -1);
ifPossible[0] = 0;

for (let i = 0; i < N; i++) {
  for (let j = 50000; j >= 0; j--) {
    if (ifPossible[j] === -1) continue;
    if (ifPossible[j] === K) continue;
    ifPossible[j + I[i]] =
      ifPossible[j + I[i]] === -1
        ? ifPossible[j] + 1
        : Math.min(ifPossible[j + I[i]], ifPossible[j] + 1);
  }
}

ansList = [];
for (let i = 1; i <= 50000; i++) {
  if (ifPossible[i] === -1) continue;
  ansList.push(i);
}

console.log(ansList.length);
console.log(ansList.join(" "));
