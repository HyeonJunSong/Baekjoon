const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const string = inp[0];

const memo1 = Array.from({ length: string.length }, () =>
  Array.from({ length: string.length }, () => -1)
);
function ifPal(st, ed) {
  if (st > ed) return 1;

  if (memo1[st][ed] !== -1) return memo1[st][ed];
  if (string[st] !== string[ed]) memo1[st][ed] = 0;
  else memo1[st][ed] = ifPal(st + 1, ed - 1);

  return memo1[st][ed];
}

const memo2 = Array.from({ length: string.length }, () => -1);
function getAns(idx) {
  if (memo2[idx] !== -1) return memo2[idx];

  let ans = 987654321;
  if (ifPal(idx, string.length - 1)) {
    memo2[idx] = 1;
    return 1;
  }

  for (let i = idx; i < string.length - 1; i++) {
    if (!ifPal(idx, i)) continue;
    ans = Math.min(ans, getAns(i + 1) + 1);
  }

  memo2[idx] = ans;
  return ans;
}

getAns(0);
console.log(getAns(0));
