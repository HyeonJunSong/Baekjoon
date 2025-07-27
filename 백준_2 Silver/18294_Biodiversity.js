const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const N = parseInt(inp[0]);
const strings = inp.slice(1, N + 1);

const strMap = new Map();

for (let i = 0; i < N; i++) {
  if (strMap.get(strings[i])) {
    strMap.set(strings[i], strMap.get(strings[i]) + 1);
  } else {
    strMap.set(strings[i], 1);
  }
}

const totSum = Array.from(strMap.entries()).reduce((prv, cur) => cur[1] + prv, 0);

let ans = "NONE";
strMap.forEach((v, k) => {
  if (totSum - v < v) ans = k;
});

console.log(ans);
