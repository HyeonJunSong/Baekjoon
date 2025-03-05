const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const [N, K] = inp[0].split(" ").map((v) => parseInt(v));
const string = inp[1];

const accumSum = Array.from({ length: 2 * N + 1 }, () => 0);
const changeIdxOf = Array.from({ length: 2 * N + 1 }, () => 0);

for (let i = 0; i < N; i++) accumSum[i] = string.charCodeAt(i) - "A".charCodeAt();
accumSum[N] = 1;
for (let i = 0; i < N; i++) accumSum[2 * N - i] = "Z".charCodeAt() - string.charCodeAt(i);

for (let i = 0; i < N; i++) changeIdxOf[i] = i;
changeIdxOf[N] = -1;
for (let i = 0; i < N; i++) changeIdxOf[2 * N - i] = i;

for (let i = 1; i < 2 * N + 1; i++) accumSum[i] += accumSum[i - 1];

if (accumSum[2 * N] < K) {
  console.log(-1);
  process.exit();
}

let st = 0;
let ed = 2 * N;

while (st <= ed) {
  const mid = (st + ed) >> 1;
  if (accumSum[mid] < K) st = mid + 1;
  else ed = mid - 1;
}

if (changeIdxOf[st] == -1) {
  console.log(string);
} else {
  const ans =
    string.slice(0, changeIdxOf[st]) +
    String.fromCharCode(
      (st < N ? 64 : string[changeIdxOf[st]].charCodeAt()) + K - (st == 0 ? 0 : accumSum[st - 1])
    ) +
    string.slice(changeIdxOf[st] + 1);
  console.log(ans);
}
