const blocks = [
  //일자
  [
    [0, 1],
    [0, 2],
    [0, 3],
  ],
  [
    [1, 0],
    [2, 0],
    [3, 0],
  ],

  //리을
  [
    [0, 1],
    [1, 1],
    [1, 2],
  ],
  [
    [1, 0],
    [1, -1],
    [2, -1],
  ],

  //기역
  [
    [0, 1],
    [0, 2],
    [1, 2],
  ],
  [
    [1, 0],
    [2, 0],
    [2, -1],
  ],
  [
    [1, 0],
    [1, 1],
    [1, 2],
  ],
  [
    [0, 1],
    [1, 0],
    [2, 0],
  ],

  //우
  [
    [0, 1],
    [0, 2],
    [1, 1],
  ],
  [
    [1, 0],
    [2, 0],
    [1, -1],
  ],
  [
    [0, 1],
    [0, 2],
    [-1, 1],
  ],
  [
    [1, 0],
    [2, 0],
    [1, 1],
  ],

  //네모
  [
    [1, 0],
    [0, 1],
    [1, 1],
  ],
];

function testCase(N, board) {
  let ans = -987654321;

  for (let i = 0; i < N; i++) {
    for (let j = 0; j < N; j++) {
      for (let k = 0; k < blocks.length; k++) {
        let curSum = board[i][j];
        for (let l = 0; l < 3; l++) {
          if (
            0 <= i + blocks[k][l][0] &&
            i + blocks[k][l][0] < N &&
            0 <= j + blocks[k][l][1] &&
            j + blocks[k][l][1] < N
          ) {
            curSum += board[i + blocks[k][l][0]][j + blocks[k][l][1]];
          } else {
            curSum = -987654321;
          }
        }
        ans = Math.max(ans, curSum);
      }
    }
  }

  return ans;
}

const fs = require("fs");
const input = fs.readFileSync("/dev/stdin").toString().split("\n");

let testCaseNum = 1;
let idx = 0;
while (true) {
  const N = parseInt(input[idx]);
  if (N == 0) break;
  const board = input.slice(idx + 1, idx + N + 1).map((v) =>
    v
      .trim()
      .split(/\s+/)
      .map((v) => parseInt(v))
  );
  console.log(`${testCaseNum}. ${testCase(N, board)}`);
  idx += N + 1;
  testCaseNum++;
}
