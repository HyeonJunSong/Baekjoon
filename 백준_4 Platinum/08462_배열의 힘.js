const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [n, t] = inp[0];
const arr = [0, ...inp[1]];
const queries = inp.slice(2, 2 + t).map((v, i) => [v, i]);

const buckets = parseInt(queries.length ** 0.5);
queries.sort((a, b) => {
  if (parseInt(a[0][0] / buckets) === parseInt(b[0][0] / buckets)) return a[0][1] - b[0][1];
  return parseInt(a[0][0] / buckets) - parseInt(b[0][0] / buckets);
});

const ans = Array.from({ length: t }, () => 0);

let curSum = 0;
const curCntOf = Array.from({ length: 10 ** 6 + 1 }, () => 0);
for (let i = queries[0][0][0]; i <= queries[0][0][1]; i++) {
  curSum -= curCntOf[arr[i]] ** 2 * arr[i];
  curSum += (++curCntOf[arr[i]]) ** 2 * arr[i];
}
ans[queries[0][1]] = curSum;

for (let i = 1; i < t; i++) {
  const [pSt, pEd] = queries[i - 1][0];
  const [nSt, nEd] = queries[i][0];
  for (let j = pSt - 1; j >= nSt; j--) {
    curSum -= curCntOf[arr[j]] ** 2 * arr[j];
    curSum += (++curCntOf[arr[j]]) ** 2 * arr[j];
  }
  for (let j = pSt; j < nSt; j++) {
    curSum -= curCntOf[arr[j]] ** 2 * arr[j];
    curSum += (--curCntOf[arr[j]]) ** 2 * arr[j];
  }
  for (let j = pEd + 1; j <= nEd; j++) {
    curSum -= curCntOf[arr[j]] ** 2 * arr[j];
    curSum += (++curCntOf[arr[j]]) ** 2 * arr[j];
  }
  for (let j = pEd; j > nEd; j--) {
    curSum -= curCntOf[arr[j]] ** 2 * arr[j];
    curSum += (--curCntOf[arr[j]]) ** 2 * arr[j];
  }

  ans[queries[i][1]] = curSum;
}

console.log(ans.join("\n"));
