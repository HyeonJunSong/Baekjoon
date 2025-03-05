const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => +v));

const [n] = inp[0];
const lotterires = Array.from({ length: n + 1 }, (v, i) => [inp[i][0], inp[i][1], i]);
lotterires[0][0] = 0;
lotterires[0][1] = 10000;

lotterires.sort((a, b) => {
  if (10000 * a[0] + a[1] * b[0] !== 10000 * b[0] + a[0] * b[1])
    return 10000 * b[0] + a[0] * b[1] - (10000 * a[0] + a[1] * b[0]);
  return a[2] - b[2];
});

console.log(
  lotterires
    .slice(1)
    .map((v) => v[2])
    .join(" ")
);
