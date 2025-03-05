const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const N = parseInt(inp[0]);

const trips = Array.from({ length: N }, (v, i) => inp[1 + i].split(" ").map((v) => parseInt(v)));

/**
 *
 * @param {number} idx : 여행 번호
 * @param {number} timeLeft : 지금 남은 시간
 * @param {number} tripCnt : 지금 여행이 할인 구간에서 몇번 째 여행인지
 */

function calcPrice(trip, tripCnt) {
  switch (tripCnt) {
    case 1:
      return trip[1];
    case 2:
      return trip[1] * 0.5;
    default:
      return trip[1] * 0.25;
  }
}

const memo = Array.from({ length: N + 1 }, () =>
  Array.from({ length: 121 }, () => Array.from({ length: 8 }, () => -1))
);

function dp(idx, timeLeft, tripCnt) {
  if (idx == N) return 0;

  if (memo[idx][timeLeft][tripCnt] != -1) return memo[idx][timeLeft][tripCnt];

  let ans = 987654321;
  //현재 여행도 할인구간에 포함하기
  if (tripCnt <= 6) {
    if (timeLeft - trips[idx][0] <= 0)
      ans = Math.min(ans, dp(idx + 1, 120, 1) + calcPrice(trips[idx], tripCnt));
    else
      ans = Math.min(
        ans,
        dp(idx + 1, timeLeft - trips[idx][0], tripCnt + 1) + calcPrice(trips[idx], tripCnt)
      );
  }

  //지금부터 새로 시작하기
  if (120 - trips[idx][0] <= 0) ans = Math.min(ans, dp(idx + 1, 120, 1) + calcPrice(trips[idx], 1));
  else ans = Math.min(ans, dp(idx + 1, 120 - trips[idx][0], 2) + calcPrice(trips[idx], 1));

  memo[idx][timeLeft][tripCnt] = ans;
  return ans;
}

console.log(dp(0, 120, 1).toFixed(2));
