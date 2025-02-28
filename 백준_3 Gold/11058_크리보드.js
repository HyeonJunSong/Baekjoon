const N = parseInt(require("fs").readFileSync("/dev/stdin"));

let ans = 0;

const memo = Array.from({ length: N + 1 }, () => -1);

function getMax(n) {
  if (n <= 6) return n;

  if (memo[n] !== -1) return memo[n];

  let ans = 0;
  for (let i = 2; i <= 5; i++) ans = Math.max(ans, (i - 1) * getMax(n - i));

  memo[n] = ans;
  return ans;
}

console.log(getMax(N));
