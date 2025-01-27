const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const strMap = new Map();
for (let i = 0; i < inp.length - 1; i++) strMap.set(inp[i], (strMap.get(inp[i]) ?? 0) + 1);

const ans = [];
let totSum = 0;
strMap.forEach((v, k) => {
  totSum += v;
  ans.push([k, v]);
});

ans.sort();
for (let i = 0; i < ans.length; i++)
  console.log(ans[i][0], ((100 * ans[i][1]) / totSum).toFixed(4));
