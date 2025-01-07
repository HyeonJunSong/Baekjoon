const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];
const childOf = Array.from({ length: N + 1 }, () => []);
const parentOf = Array.from({ length: N + 1 }, () => []);

for (let i = 0; i < M; i++) {
  childOf[inp[1 + i][0]].push(inp[1 + i][1]);
  parentOf[inp[1 + i][1]].push(inp[1 + i][0]);
}

class PQ {
  constructor() {
    this.lis = [null];
  }

  swap(idx1, idx2) {
    [this.lis[idx1], this.lis[idx2]] = [this.lis[idx2], this.lis[idx1]];
  }
  empty() {
    return this.lis.length == 1;
  }

  push(val) {
    let idx = this.lis.length;
    this.lis.push(val);

    while (idx > 1) {
      if (this.lis[idx >> 1] <= this.lis[idx]) break;
      this.swap(idx >> 1, idx);
      idx >>= 1;
    }
  }

  pop() {
    const popVal = this.lis[1];
    this.swap(1, this.lis.length - 1);
    this.lis.pop();
    let idx = 1;
    while (2 * idx < this.lis.length) {
      if (2 * idx + 1 < this.lis.length && this.lis[2 * idx] > this.lis[2 * idx + 1]) {
        if (this.lis[idx] < this.lis[2 * idx + 1]) break;
        this.swap(idx, 2 * idx + 1);
        idx = 2 * idx + 1;
      } else {
        if (this.lis[idx] < this.lis[2 * idx]) break;
        this.swap(idx, 2 * idx);
        idx = 2 * idx;
      }
    }

    return popVal;
  }
}

const pq = new PQ();

for (let i = 1; i <= N; i++) {
  if (parentOf[i].length > 0) continue;
  pq.push(i);
}

const ans = [];

const parentVisitCnt = Array.from({ length: N + 1 }, () => 0);

while (!pq.empty()) {
  const cur = pq.pop();
  ans.push(cur);

  for (let i = 0; i < childOf[cur].length; i++) {
    parentVisitCnt[childOf[cur][i]]++;
    if (parentVisitCnt[childOf[cur][i]] < parentOf[childOf[cur][i]].length) continue;
    pq.push(childOf[cur][i]);
  }
}

console.log(ans.join(" "));
