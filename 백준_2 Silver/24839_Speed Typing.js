const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

let idx = 0;
const T = parseInt(inp[idx++]);

function solve(I, P) {
  let ans = 0;
  let pIdx = 0;
  for (let i = 0; i < I.length; i++) {
    while (pIdx < P.length && I[i] != P[pIdx]) {
      pIdx++;
      ans++;
    }

    if (pIdx == P.length) return "IMPOSSIBLE";

    pIdx++;
  }
  if (pIdx < P.length) ans += P.length - pIdx;

  return ans;
}

for (let t = 0; t < T; t++) {
  const I = inp[idx++];
  const P = inp[idx++];

  console.log(`Case #${t + 1}: ${solve(I, P)}`);
}
