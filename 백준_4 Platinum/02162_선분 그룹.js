const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [N] = inp[0];
const lines = inp.slice(1);

//a 에 대해 b가 ccw인지
//1이면 ccw, 0이면 parellel, -1이면 cw
function ccw(a, b) {
  const d = a[0] * b[1] - a[1] * b[0];
  if (d === 0) return 0;
  if (d > 0) return 1;
  else return -1;
}

function ifCross(line1, line2) {
  const A1A2B1 = ccw(
    [line1[2] - line1[0], line1[3] - line1[1]],
    [line2[0] - line1[0], line2[1] - line1[1]]
  );
  const A1A2B2 = ccw(
    [line1[2] - line1[0], line1[3] - line1[1]],
    [line2[2] - line1[0], line2[3] - line1[1]]
  );
  const B1B2A1 = ccw(
    [line2[2] - line2[0], line2[3] - line2[1]],
    [line1[0] - line2[0], line1[1] - line2[1]]
  );
  const B1B2A2 = ccw(
    [line2[2] - line2[0], line2[3] - line2[1]],
    [line1[2] - line2[0], line1[3] - line2[1]]
  );

  if (A1A2B1 === 0 && A1A2B2 === 0) {
    return !(
      Math.max(line1[0], line1[2]) < Math.min(line2[0], line2[2]) ||
      Math.max(line2[0], line2[2]) < Math.min(line1[0], line1[2]) ||
      Math.max(line1[1], line1[3]) < Math.min(line2[1], line2[3]) ||
      Math.max(line2[1], line2[3]) < Math.min(line1[1], line1[3])
    );
  }

  return A1A2B1 !== A1A2B2 && B1B2A1 !== B1B2A2;
}

const graph = Array.from({ length: N }, () => []);
for (let i = 0; i < N; i++) {
  for (let j = i + 1; j < N; j++) {
    if (!ifCross(lines[i], lines[j])) continue;
    graph[i].push(j);
    graph[j].push(i);
  }
}

let ansCnt = 0;
let ansVal = 0;

const visited = Array.from({ length: N }, () => false);
for (let i = 0; i < N; i++) {
  if (visited[i]) continue;

  visited[i] = true;
  const s = [i];

  ansCnt += 1;
  let curVal = 0;

  while (s.length > 0) {
    const cur = s[s.length - 1];
    s.pop();

    curVal += 1;

    for (let j = 0; j < graph[cur].length; j++) {
      if (visited[graph[cur][j]]) continue;
      visited[graph[cur][j]] = true;
      s.push(graph[cur][j]);
    }
  }

  ansVal = Math.max(ansVal, curVal);
}

console.log(ansCnt);
console.log(ansVal);
