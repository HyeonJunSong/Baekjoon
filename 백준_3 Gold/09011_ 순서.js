const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let inpIdx = 0;
const [T] = inp[inpIdx++];

function testCase() {
  const [n] = inp[inpIdx++];
  const R = inp[inpIdx++];

  if (R[0] !== 0) {
    console.log("IMPOSSIBLE");
    return;
  }

  const priorityList = [[0, 0]];

  for (let i = 1; i < n; i++) {
    priorityList.sort((a, b) => a[0] - b[0]);

    if (R[i] > i) {
      console.log("IMPOSSIBLE");
      return;
    }

    if (R[i] === i) priorityList.push([priorityList[priorityList.length - 1][0] + 100, i]);
    else if (R[i] === 0) priorityList.push([priorityList[0][0] - 100, i]);
    else priorityList.push([(priorityList[R[i] - 1][0] + priorityList[R[i]][0]) / 2, i]);
  }
  priorityList.sort((a, b) => a[0] - b[0]);

  const ans = Array.from({ length: n }, () => 0);
  for (let i = 0; i < n; i++) ans[priorityList[i][1]] = i + 1;

  console.log(ans.join(" "));
}

for (let t = 0; t < T; t++) testCase();
