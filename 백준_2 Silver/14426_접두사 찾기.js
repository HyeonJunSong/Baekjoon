const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [N, M] = inp[0].split(" ").map((v) => parseInt(v));

const tri = Array.from({ length: 26 }, () => null);
for (let i = 0; i < N; i++) {
  let cur = tri;
  for (let j = 0; j < inp[1 + i].length; j++) {
    if (cur[inp[1 + i].charCodeAt(j) - 97] === null)
      cur[inp[1 + i].charCodeAt(j) - 97] = Array.from({ length: 26 }, () => null);
    cur = cur[inp[1 + i].charCodeAt(j) - 97];
  }
}

let ans = M;
for (let i = 0; i < M; i++) {
  let cur = tri;
  for (let j = 0; j < inp[1 + N + i].length; j++) {
    if (cur[inp[1 + N + i].charCodeAt(j) - 97] === null) {
      ans--;
      break;
    }
    cur = cur[inp[1 + N + i].charCodeAt(j) - 97];
  }
}

console.log(ans);
