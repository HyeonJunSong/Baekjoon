const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().replace("\n", "");

const [L, R] = inp.split("::").map((v) => v.split(":"));

const ans = Array.from({ length: 8 }, () => Array.from({ length: 4 }, () => "0"));
if (L !== undefined) {
  for (let i = 0; i < L.length; i++) {
    for (let j = 0; j < L[i].length; j++) {
      ans[i][4 - j - 1] = L[i][L[i].length - j - 1];
    }
  }
}
if (R !== undefined) {
  for (let i = 0; i < R.length; i++) {
    for (let j = 0; j < R[R.length - i - 1].length; j++) {
      ans[8 - i - 1][4 - j - 1] = R[R.length - i - 1][R[R.length - i - 1].length - j - 1];
    }
  }
}

console.log(ans.map((v) => v.join("")).join(":"));
