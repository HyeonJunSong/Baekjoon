const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, F] = inp[0];

function combination(n, r) {
  if (r === n) return 1;
  if (r === 0) return 1;

  return combination(n - 1, r - 1) + combination(n - 1, r);
}

const combs = Array.from({ length: N }, (_, i) => combination(N - 1, i));

const ans = Array.from({ length: N }, () => 0);
function getAns(idx, visited, f, s) {
  if (f < 0) {
    return false;
  }

  if (idx == N) {
    if (f === 0) {
      s.forEach((v, i) => (ans[i] = v));
      return true;
    }
    return false;
  }

  for (let i = 0; i < N; i++) {
    if (visited[i]) continue;
    visited[i] = true;
    s.push(i + 1);
    if (getAns(idx + 1, visited, f - combs[idx] * (i + 1), s)) return true;
    s.pop();
    visited[i] = false;
  }

  return false;
}

getAns(
  0,
  Array.from({ length: N }, () => false),
  F,
  []
);

console.log(ans.join(" "));
