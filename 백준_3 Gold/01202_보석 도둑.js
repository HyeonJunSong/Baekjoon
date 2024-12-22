class PQ {
  constructor() {
    this.list = [null];
  }

  isEmpty() {
    return this.list.length == 1;
  }

  push(val) {
    let idx = this.list.length;
    this.list.push(val);
    while (idx > 1) {
      const nxtIdx = parseInt(idx / 2);
      if (this.list[idx] <= this.list[nxtIdx]) break;
      [this.list[idx], this.list[nxtIdx]] = [this.list[nxtIdx], this.list[idx]];
      idx = nxtIdx;
    }
  }

  pop() {
    const popVal = this.list[1];
    [this.list[1], this.list[this.list.length - 1]] = [
      this.list[this.list.length - 1],
      this.list[1],
    ];
    this.list.pop();

    let idx = 1;
    while (idx * 2 < this.list.length) {
      if (idx * 2 + 1 < this.list.length && this.list[idx * 2 + 1] > this.list[idx * 2]) {
        if (this.list[2 * idx + 1] <= this.list[idx]) break;
        [this.list[idx], this.list[2 * idx + 1]] = [this.list[2 * idx + 1], this.list[idx]];
        idx = 2 * idx + 1;
      } else {
        if (this.list[2 * idx] <= this.list[idx]) break;
        [this.list[idx], this.list[2 * idx]] = [this.list[2 * idx], this.list[idx]];
        idx = 2 * idx;
      }
    }

    return popVal;
  }
}

const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, K] = inp[0];
const jewels = inp.slice(1, N + 1);
const bags = inp.slice(1 + N).map((v) => v[0]);

jewels.sort((a, b) => a[0] - b[0]);
bags.sort((a, b) => a - b);

const pq = new PQ();

let jewelIdx = 0;
let ans = 0;
for (let i = 0; i < K; i++) {
  while (jewelIdx < N && jewels[jewelIdx][0] <= bags[i]) {
    pq.push(jewels[jewelIdx][1]);
    jewelIdx++;
  }

  if (pq.isEmpty()) continue;
  ans += pq.pop();
}

console.log(ans);
