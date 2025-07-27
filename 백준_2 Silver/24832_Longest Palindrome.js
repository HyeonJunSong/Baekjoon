const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [n, m] = inp[0].split(" ").map((v) => parseInt(v));
const strings = inp.slice(1, n + 1);

const isSelected = Array.from({ length: n }, () => false);

const lStack = [];
const rStack = [];

for (let i = 0; i < n - 1; i++) {
  if (isSelected[i]) continue;
  for (let j = i + 1; j < n; j++) {
    let isSymm = true;
    for (let k = 0; k < m; k++) {
      if (strings[i][k] !== strings[j][m - k - 1]) {
        isSymm = false;
        break;
      }
    }
    if (isSymm) {
      lStack.push(i);
      rStack.push(j);
      isSelected[i] = true;
      isSelected[j] = true;
      break;
    }
  }
}

let mid = -1;
for (let i = 0; i < n; i++) {
  if (isSelected[i]) continue;
  let isPal = true;
  for (let j = 0; j < m; j++) {
    if (strings[i][j] !== strings[i][m - j - 1]) {
      isPal = false;
      break;
    }
  }
  if (isPal) {
    mid = i;
    break;
  }
}

let ans = "";
ans += lStack.map((v) => strings[v]).join("");
ans += mid !== -1 ? strings[mid] : "";
ans += rStack
  .reverse()
  .map((v) => strings[v])
  .join("");

console.log(ans.length);
if (ans.length > 0) console.log(ans);
