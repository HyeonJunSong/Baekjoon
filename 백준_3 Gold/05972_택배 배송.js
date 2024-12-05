class PQ {
  constructor() {
    this.list = [null];
  }
  static defaultVal = [0, 987654321];

  empty() {
    return this.list.length == 1;
  }

  comp(a, b) {
    return (a === undefined ? PQ.defaultVal : a)[1] > (b === undefined ? PQ.defaultVal : b)[1];
  }

  pop() {
    const top = this.list[1];
    let idx = 1;
    while (2 * idx < this.list.length) {
      if (this.comp(this.list[2 * idx], this.list[2 * idx + 1])) {
        [this.list[idx], this.list[2 * idx + 1]] = [this.list[2 * idx + 1], this.list[idx]];
        idx = 2 * idx + 1;
      } else {
        [this.list[idx], this.list[2 * idx]] = [this.list[2 * idx], this.list[idx]];
        idx = 2 * idx;
      }
    }

    [this.list[idx], this.list[this.list.length - 1]] = [
      this.list[this.list.length - 1],
      this.list[idx],
    ];
    this.list.pop();

    while (idx > 1) {
      if (this.comp(this.list[parseInt(idx / 2)], this.list[idx])) {
        [this.list[parseInt(idx / 2)], this.list[idx]] = [
          this.list[idx],
          this.list[parseInt(idx / 2)],
        ];
      }
      idx = parseInt(idx / 2);
    }

    return top;
  }

  insert(val) {
    this.list.push(val);
    let idx = this.list.length - 1;
    while (idx > 1) {
      if (this.comp(this.list[parseInt(idx / 2)], this.list[idx])) {
        [this.list[parseInt(idx / 2)], this.list[idx]] = [
          this.list[idx],
          this.list[parseInt(idx / 2)],
        ];
      }
      idx = parseInt(idx / 2);
    }
  }
}

const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N, M] = inp[0];

const farm = Array.from({ length: N + 1 }, () => []);
for (let i = 0; i < M; i++) {
  farm[inp[1 + i][0]].push([inp[1 + i][1], inp[1 + i][2]]);
  farm[inp[1 + i][1]].push([inp[1 + i][0], inp[1 + i][2]]);
}

const pq = new PQ();
pq.insert([1, 0]);

const visited = Array(N + 1).fill(987654321);

while (!pq.empty()) {
  const cur = pq.pop();

  if (visited[cur[0]] <= cur[1]) continue;
  visited[cur[0]] = cur[1];

  for (let i = 0; i < farm[cur[0]].length; i++) {
    pq.insert([farm[cur[0]][i][0], cur[1] + farm[cur[0]][i][1]]);
  }
}

console.log(visited[N]);
