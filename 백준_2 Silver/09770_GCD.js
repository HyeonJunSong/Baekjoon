const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let nums = [];
inp.forEach((v) => (nums = [...nums, ...v]));

function GCD(a, b) {
  if (a > b) [a, b] = [b, a];
  while (a > 0) [a, b] = [b % a, a];

  return b;
}

let ans = 0;
for (let i = 0; i < nums.length; i++) {
  for (let j = i + 1; j < nums.length; j++) {
    if (isNaN(nums[i]) || isNaN(nums[j])) continue;
    ans = Math.max(ans, GCD(nums[i], nums[j]));
  }
}

console.log(ans);
