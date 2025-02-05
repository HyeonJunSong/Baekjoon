const fs = require("fs");
let [A, B] = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split(" ")
  .map((v) => parseInt(v));

if (B % A !== 0) {
  console.log(0);
  process.exit(0);
}

B /= A;

const divisors = new Map();
let idx = 2;
while (B > 1) {
  if (B % idx !== 0) {
    idx++;
    continue;
  }

  divisors.set(idx, (divisors.get(idx) ?? 0) + 1);
  B /= idx;
}

let ans = 1;

divisors.forEach((v) => (ans *= v + 1));

console.log(ans);
