const fs = require("fs");
const [n, m] = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split(" ")
  .map((v) => parseInt(v));

const ans = [];
for (let i = 2; i <= n; i += 2) ans.push(`${i} 1 ${i} ${m}`);
for (let j = 2; j <= m; j += 2) ans.push(`1 ${j} ${n} ${j}`);

console.log(ans.length);
console.log(ans.join("\n"));
