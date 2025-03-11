const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const b = inp[0];

const memo = Array.from({ length: 2 }, () =>
  Array.from({ length: 501 }, () => Array.from({ length: 501 }, () => -1))
);

function ifAWins(isATurn, boxAleft, boxBleft) {
  if (memo[isATurn][boxAleft][boxBleft] !== -1) return memo[isATurn][boxAleft][boxBleft];

  let ans = isATurn ? false : true;
  if (isATurn) {
    for (let i = 0; i < 3; i++) {
      if (boxAleft >= b[i] && ifAWins(0, boxAleft - b[i], boxBleft)) {
        ans = !ans;
        break;
      }
      if (boxBleft >= b[i] && ifAWins(0, boxAleft, boxBleft - b[i])) {
        ans = !ans;
        break;
      }
    }
  } else {
    for (let i = 0; i < 3; i++) {
      if (boxAleft >= b[i] && !ifAWins(1, boxAleft - b[i], boxBleft)) {
        ans = !ans;
        break;
      }
      if (boxBleft >= b[i] && !ifAWins(1, boxAleft, boxBleft - b[i])) {
        ans = !ans;
        break;
      }
    }
  }

  memo[isATurn][boxAleft][boxBleft] = ans;
  return ans;
}

for (let t = 0; t < 5; t++) console.log(ifAWins(1, inp[1 + t][0], inp[1 + t][1]) ? "A" : "B");
