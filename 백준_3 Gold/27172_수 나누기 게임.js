const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const nums = inp[1];

const idxOf = Array.from({ length: 1000001 }, () => -1);
nums.forEach((v, i) => (idxOf[v] = i));

const ans = Array.from({ length: N }, () => 0);

for (let i = 1; i <= 1000000; i++) {
  if (idxOf[i] == -1) continue;
  for (let j = 2 * i; j <= 1000000; j += i) {
    if (idxOf[j] == -1) continue;
    ans[idxOf[i]]++;
    ans[idxOf[j]]--;
  }
}

console.log(ans.join(" "));
