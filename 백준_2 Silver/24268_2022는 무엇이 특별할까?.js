const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split(" ")
  .map((v) => parseInt(v));

const [N, d] = inp;

function toNDigit(num, N) {
  const res = [];
  while (num > 0) {
    res.push(num % N);
    num = parseInt(num / N);
  }
  return res.reverse().join("");
}

function to10Digit(num, N) {
  let res = 0;
  let curBase = 1;
  for (let i = 0; i < num.length; i++) {
    res += parseInt(num[num.length - 1 - i]) * curBase;
    curBase *= N;
  }
  return res;
}

function permutation(res, visited, n, cur, cnt) {
  if (cnt == n) {
    res.push(to10Digit(cur, d));
    return;
  }
  for (let i = 0; i < n; i++) {
    if (visited[i]) continue;

    visited[i] = true;
    permutation(res, visited, n, cur + i.toString(), cnt + 1);
    visited[i] = false;
  }
}

const converted = toNDigit(N, d);
if (converted.length > d) {
  console.log(-1);
} else if (converted.length < d) {
  console.log(to10Digit("10" + Array.from({ length: d - 2 }, (v, i) => i + 2).join(""), d));
} else {
  const p = [];
  permutation(
    p,
    Array.from({ length: d }, () => false),
    d,
    "",
    0
  );
  p.sort((a, b) => a - b);

  let st = 0;
  let ed = p.length - 1;

  while (st <= ed) {
    const mid = (st + ed) >> 1;
    if (p[mid] <= N) st = mid + 1;
    else ed = mid - 1;
  }

  if (st === p.length) console.log(-1);
  else console.log(p[st]);
}
