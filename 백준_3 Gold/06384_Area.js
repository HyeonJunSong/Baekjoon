const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

let inpIdx = 0;
const [T] = inp[inpIdx++];

function getGCD(a, b) {
  if (a > b) [a, b] = [b, a];
  while (a > 0) [a, b] = [b % a, a];
  return b;
}

/**
 * 벡터 p1p2에 대해 벡터 p2p3가 CCW 인지 여부 리턴
 */
function isCCW(p1, p2, p3) {
  const base = [p2[0] - p1[0], p2[1] - p1[1]];
  const target = [p3[0] - p2[0], p3[1] - p2[1]];
  return base[0] * target[1] - base[1] * target[0] > 0;
}

function areaOfTriangle(p0, p1, p2) {
  return (
    Math.abs(
      p0[0] * p1[1] + p1[0] * p2[1] + p2[0] * p0[1] - p0[1] * p1[0] - p1[1] * p2[0] - p2[1] * p0[0]
    ) / 2
  );
}

function testCase() {
  const [m] = inp[inpIdx++];
  moves = inp.slice(inpIdx, inpIdx + m);
  inpIdx += m;

  let [I, E, A] = [0, 0, 0];

  ////테두리 점 개수 구하기
  //벡터 돌면서 직접 구하면 됨
  //벡터 [a, b] 가 지나는 점 개수는 a, b의 최대 공약수 + 1
  for (let i = 0; i < m; i++) E += getGCD(Math.abs(moves[i][0]), Math.abs(moves[i][1]));

  ////내부 넓이 구하기
  //벡터 돌면서 삼각형으로 쪼개서 구하기
  //P0 - Pi - Pi+1 삼각형을
  //반시계 방향이면 더하고, 시계방향이면 빼기
  const points = [[0, 0]];
  for (let i = 0; i < m; i++)
    points.push([
      points[points.length - 1][0] + moves[i][0],
      points[points.length - 1][1] + moves[i][1],
    ]);

  for (let i = 1; i < points.length - 1; i++)
    A +=
      areaOfTriangle(points[0], points[i], points[i + 1]) *
      (isCCW(points[0], points[i], points[i + 1]) ? 1 : -1);

  ////내부 점 개수 구하기
  //픽의 정리
  //A = I + E / 2 - 1
  I = A - E / 2 + 1;

  console.log(I, E, A.toFixed(1));
}

for (let t = 0; t < T; t++) {
  console.log(`Scenario #${t + 1}:`);
  testCase();
  console.log();
}
