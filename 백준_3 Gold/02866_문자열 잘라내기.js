const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const [R, C] = inp[0].split(" ").map((v) => parseInt(v));
const matrix = inp.slice(1);

let count = 0;
let curR = 0;
while (curR < R - 1) {
  const sortedArr = Array.from({ length: C }, (v, i) => i).sort((a, b) => {
    let idx = curR + 1;
    while (idx < R && matrix[idx][a].charCodeAt() === matrix[idx][b].charCodeAt()) idx++;
    if (idx === R) return 1;
    return matrix[idx][a].charCodeAt() - matrix[idx][b].charCodeAt();
  });

  let ifOverlaped = false;
  for (let i = 0; i < C - 1; i++) {
    let idx = curR + 1;
    while (
      idx < R &&
      matrix[idx][sortedArr[i]].charCodeAt() === matrix[idx][sortedArr[i + 1]].charCodeAt()
    )
      idx++;
    if (idx !== R) continue;

    ifOverlaped = true;
    break;
  }

  if (ifOverlaped) break;

  count++;
  curR++;
}

console.log(count);
