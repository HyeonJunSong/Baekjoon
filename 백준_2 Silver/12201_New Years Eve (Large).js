const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [T] = inp[0];

function testCase(B, L, N) {
  const glasses = Array.from({ length: L + 1 }, (_, i) => Array.from({ length: i }, () => 0));

  glasses[1][0] = 750 * B;

  for (let i = 1; i < L; i++) {
    for (let j = i; j > 0; j--) {
      for (let k = 0; k < glasses[j].length; k++) {
        if (glasses[j][k] <= 250) {
          glasses[j][k] = 0;
          continue;
        }

        let curOverflowed = glasses[j][k] - 250;
        glasses[j + 1][k] += curOverflowed / 3;
        glasses[j + 1][k + 1] += curOverflowed / 3;
        glasses[j][k] = curOverflowed / 3;
      }
    }
  }

  let idx = 1;
  let i = 1,
    j = 0;
  while (idx < N) {
    if (glasses[i].length - 1 === j) {
      i++;
      j = 0;
    } else {
      j++;
    }
    idx++;
  }

  return Math.min(250, glasses[i][j]);
}

for (let t = 0; t < T; t++) console.log(`Case #${t + 1}: ${testCase(...inp[1 + t]).toFixed(7)}`);
