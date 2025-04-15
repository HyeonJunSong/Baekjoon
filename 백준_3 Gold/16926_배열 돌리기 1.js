const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M, R] = inp[0];
const arr = inp.slice(1, 1 + N);

const layerCnt = Math.min(N, M) / 2;
const numOf = Array.from({ length: layerCnt }, () => []);
for (let i = 0; i < layerCnt; i++) {
  for (let j = 0; j < M - i * 2 - 1; j++) numOf[i].push(arr[i][i + j]);
  for (let j = 0; j < N - i * 2 - 1; j++) numOf[i].push(arr[i + j][M - i - 1]);
  for (let j = 0; j < M - i * 2 - 1; j++) numOf[i].push(arr[N - i - 1][M - i - 1 - j]);
  for (let j = 0; j < N - i * 2 - 1; j++) numOf[i].push(arr[N - i - 1 - j][i]);
}

const ans = Array.from({ length: N }, () => Array.from({ length: M }, () => 0));
for (let i = 0; i < layerCnt; i++) {
  let idx = 0;
  for (let j = 0; j < M - i * 2 - 1; j++) ans[i][i + j] = numOf[i][(idx++ + R) % numOf[i].length];
  for (let j = 0; j < N - i * 2 - 1; j++)
    ans[i + j][M - i - 1] = numOf[i][(idx++ + R) % numOf[i].length];
  for (let j = 0; j < M - i * 2 - 1; j++)
    ans[N - i - 1][M - i - 1 - j] = numOf[i][(idx++ + R) % numOf[i].length];
  for (let j = 0; j < N - i * 2 - 1; j++)
    ans[N - i - 1 - j][i] = numOf[i][(idx++ + R) % numOf[i].length];
}

for (let i = 0; i < N; i++) console.log(ans[i].join(" "));
