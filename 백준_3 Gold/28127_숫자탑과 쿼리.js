const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

function getFloor(a, d, x) {
  const A = d;
  const B = 2 * a - d;
  const C = -2 * x;
  return Math.floor((-B + Math.sqrt(B ** 2 - 4 * A * C)) / (2 * A));
}

function getOffset(a, d, x, floor) {
  return x - a * floor - (d * floor * (floor - 1)) / 2;
}

const [Q] = inp[0];
const ans = [];
for (let q = 0; q < Q; q++) {
  const [a, d, x] = inp[1 + q];
  const floor = getFloor(a, d, x);
  const offset = getOffset(a, d, x, floor);

  if (offset === 0) ans.push(`${floor} ${a + (floor - 1) * d}`);
  else ans.push(`${floor + 1} ${offset}`);
}

console.log(ans.join("\n"));
