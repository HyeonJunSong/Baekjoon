const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => BigInt(v)));

let N = inp[0];

const factorialOf = Array.from({ length: N + 1 }, () => 1n);
for (let i = 2; i <= 20; i++) factorialOf[i] = factorialOf[i - 1] * BigInt(i);

const problem = inp[1][0];

if (problem === 1n) {
  let k = BigInt(inp[1][1]);

  const ans = [];
  const visited = Array.from({ length: N + 1 }, () => false);

  for (let i = 1; i <= N; i++) {
    for (let j = 1; j <= N; j++) {
      if (visited[j]) continue;
      if (k > factorialOf[N - i]) {
        k -= factorialOf[N - i];
        continue;
      }
      ans.push(j);
      visited[j] = true;
      break;
    }
  }

  console.log(ans.join(" "));
} else {
  let arr = inp[1].slice(1);

  let ans = 1n;

  const visited = Array.from({ length: N + 1 }, () => false);
  for (let i = 0; i < N; i++) {
    let curFrontCnt = 0;
    for (let j = 1; j <= N; j++) {
      if (visited[j]) continue;
      if (arr[i] > j) {
        curFrontCnt++;
        continue;
      }
      break;
    }
    visited[arr[i]] = true;
    ans += factorialOf[N - i - 1] * BigInt(curFrontCnt);
  }

  console.log(ans.toString());
}
