const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const circles = inp
  .slice(1)
  .map((v) => [v[0] - v[1], v[0] + v[1]])
  .sort((a, b) => {
    if (a[0] !== b[0]) return a[0] - b[0];
    return a[1] - b[1];
  });

for (let i = 0; i < N - 1; i++) {
  if (circles[i][0] === circles[i + 1][0]) {
    console.log("NO");
    process.exit();
  }
}

const stack = [];
for (let i = 0; i < N; i++) {
  while (stack.length > 0 && stack[stack.length - 1] < circles[i][0]) stack.pop();

  if (stack.length > 0 && stack[stack.length - 1] <= circles[i][1]) {
    console.log("NO");
    process.exit();
  }
  stack.push(circles[i][1]);
}
console.log("YES");
