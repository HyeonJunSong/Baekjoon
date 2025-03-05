const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let inpIdx = 0;

const halfDegree = Math.atan2(0, -1);

const [T] = inp[inpIdx++];
for (let t = 0; t < T; t++) testCase();

function testCase() {
  const [N] = inp[inpIdx++];
  const targets = Array.from({ length: N }, () => inp[inpIdx++]);

  const degreeMap = new Map([
    [-halfDegree, 0],
    [halfDegree, 0],
  ]);
  for (let i = 0; i < N; i++) {
    let st = Math.atan2(targets[i][1], targets[i][0]);
    let ed = Math.atan2(targets[i][3], targets[i][2]);

    if (ed < st) [st, ed] = [ed, st];
    if (ed - st > halfDegree) [st, ed] = [ed, st];

    if (ed < st) {
      degreeMap.set(st, (degreeMap.get(st) ?? 0) + 1);
      degreeMap.set(halfDegree, (degreeMap.get(halfDegree) ?? 0) - 1);

      degreeMap.set(-halfDegree, (degreeMap.get(-halfDegree) ?? 0) + 1);
      degreeMap.set(ed, (degreeMap.get(ed) ?? 0) - 1);
    } else {
      degreeMap.set(st, (degreeMap.get(st) ?? 0) + 1);
      degreeMap.set(ed, (degreeMap.get(ed) ?? 0) - 1);
    }
  }

  const degreeAccum = [];
  degreeMap.forEach((v, k) => degreeAccum.push([k, v]));
  degreeAccum.sort((a, b) => a[0] - b[0]);

  for (let i = 1; i < degreeAccum.length; i++) degreeAccum[i][1] += degreeAccum[i - 1][1];

  let ans = 0;
  for (let i = 0; i < degreeAccum.length - 1; i++)
    ans += degreeAccum[i][1] * (degreeAccum[i + 1][0] - degreeAccum[i][0]);
  console.log((ans / (2 * halfDegree)).toFixed(5));
}
