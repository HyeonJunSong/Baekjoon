const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => +v));

const [N] = inp[0];
const solutions = inp[1];

//3번째 용액 탐색을 매개변수 탐색 하기 위해 정렬
solutions.sort((a, b) => a - b);

//두 용액을 navie 하게 섞고, 마지막 용액을 매개변수 탐색으로 찾기
let ansSum = Infinity;
const ansSet = [0, 0, 0];

for (let i = 0; i < N - 2; i++) {
  for (let j = i + 1; j < N - 1; j++) {
    //매개변수 탐색
    let st = j + 1;
    let ed = N - 1;
    const target = -(solutions[i] + solutions[j]);

    while (st <= ed) {
      const mid = (st + ed) >> 1;

      if (solutions[mid] < target) st = mid + 1;
      else ed = mid - 1;
    }

    //정답 도출
    if (ed > j) {
      if (ansSum > Math.abs(solutions[i] + solutions[j] + solutions[ed])) {
        ansSum = Math.abs(solutions[i] + solutions[j] + solutions[ed]);
        [ansSet[0], ansSet[1], ansSet[2]] = [solutions[i], solutions[j], solutions[ed]];
      }
    }
    if (st < N) {
      if (ansSum > Math.abs(solutions[i] + solutions[j] + solutions[st])) {
        ansSum = Math.abs(solutions[i] + solutions[j] + solutions[st]);
        [ansSet[0], ansSet[1], ansSet[2]] = [solutions[i], solutions[j], solutions[st]];
      }
    }
  }
}

console.log(ansSet.join(" "));
