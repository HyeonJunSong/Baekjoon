const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const badScore = Array.from({ length: 1000001 }, (v, i) => i);
for (let i = 1; i <= 1000000; i++) for (let j = i + i; j <= 1000000; j += i) badScore[j] -= i;
for (let i = 1; i <= 1000000; i++) badScore[i] = Math.abs(badScore[i]);

let idx = 0;
while (true) {
  const [start, stop, badness] = inp[idx++];
  if (start === 0) break;

  let ans = 0;
  for (let i = start; i <= stop; i++) if (badScore[i] <= badness) ans++;
  console.log(`Test ${idx}: ${ans}`);
}
