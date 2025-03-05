const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M, K] = inp[0];
const cards = inp[1];
const chulSu = inp[2];

const visited = Array.from({ length: M }, () => false);
cards.sort((a, b) => a - b);

const ans = [];
for (let i = 0; i < K; i++) {
  let st = 0;
  let ed = M - 1;

  while (st <= ed) {
    const mid = parseInt((st + ed) / 2);

    if (cards[mid] <= chulSu[i]) st = mid + 1;
    else ed = mid - 1;
  }

  while (visited[st]) st += 1;

  ans.push(cards[st]);
  visited[st] = true;
}

console.log(ans.join("\n"));
