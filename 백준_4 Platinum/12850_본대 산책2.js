const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
let D = parseInt(inp[0]);

const m = [
  [0n, 1n, 1n, 0n, 0n, 0n, 0n, 0n],
  [1n, 0n, 1n, 1n, 0n, 0n, 0n, 0n],
  [1n, 1n, 0n, 1n, 1n, 0n, 0n, 0n],
  [0n, 1n, 1n, 0n, 1n, 1n, 0n, 0n],
  [0n, 0n, 1n, 1n, 0n, 1n, 1n, 0n],
  [0n, 0n, 0n, 1n, 1n, 0n, 0n, 1n],
  [0n, 0n, 0n, 0n, 1n, 0n, 0n, 1n],
  [0n, 0n, 0n, 0n, 0n, 1n, 1n, 0n],
];

const resM = [
  [1n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
  [0n, 0n, 0n, 0n, 0n, 0n, 0n, 0n],
];

while (D > 0) {
  if (D % 2 == 1) {
    const resMCp = Array.from({ length: 8 }, () => Array.from({ length: 8 }, () => 0n));
    for (let i = 0; i < 8; i++)
      for (let j = 0; j < 8; j++)
        for (let k = 0; k < 8; k++)
          resMCp[i][j] = (resMCp[i][j] + ((resM[i][k] * m[k][j]) % 1000000007n)) % 1000000007n;
    for (let i = 0; i < 8; i++) for (let j = 0; j < 8; j++) resM[i][j] = resMCp[i][j];
  }

  const mCp = Array.from({ length: 8 }, () => Array.from({ length: 8 }, () => 0n));
  for (let i = 0; i < 8; i++)
    for (let j = 0; j < 8; j++)
      for (let k = 0; k < 8; k++)
        mCp[i][j] = (mCp[i][j] + ((m[i][k] * m[k][j]) % 1000000007n)) % 1000000007n;
  for (let i = 0; i < 8; i++) for (let j = 0; j < 8; j++) m[i][j] = mCp[i][j];

  D >>= 1;
}

console.log(parseInt(resM[0][0]));
