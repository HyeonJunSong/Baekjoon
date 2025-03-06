const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [R, C] = inp[0].split(" ").map((v) => parseInt(v));
const home = inp.slice(1, 1 + R);

const maxHeightOf = Array.from({ length: C }, () => Array.from({ length: R + 1 }, () => 0));
let ans = 0;
for (let i = R - 1; i >= 0; i--) {
  for (let j = C - 1; j >= 0; j--) {
    for (let w = 0; w < C - j; w++) {
      if (home[i][j + w] === "X") {
        maxHeightOf[j][w] = 0;
        continue;
      }
      if (w > 0 && maxHeightOf[j][w - 1] === 0) {
        maxHeightOf[j][w] = 0;
        continue;
      }
      maxHeightOf[j][w]++;

      ans = Math.max(ans, 2 * (w + 1 + maxHeightOf[j][w]) - 1);
    }
  }
}

console.log(ans);
