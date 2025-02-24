const n = parseInt(require("fs").readFileSync("/dev/stdin").toString());

function decomposeLoc(loc) {
  const level = Math.floor((-1 + Math.sqrt(1 + 8 * loc)) / 2) + 1;
  const offset = loc - (level * (level - 1)) / 2;

  return [level, offset];
}

function composeLoc(level, offset) {
  return (level * (level - 1)) / 2 + offset;
}

const memo = Array.from({ length: composeLoc(n + 1, 0) }, () =>
  Array.from({ length: composeLoc(n + 1, 0) }, () => -1)
);
function getNumOf(loc1, loc2) {
  if (memo[loc1][loc2] !== -1) return memo[loc1][loc2];

  const [level, loc1Offset] = decomposeLoc(loc1);
  const [, loc2Offset] = decomposeLoc(loc2);

  if (level === n) return 1;

  let ans = 0;
  for (let i = 0; i <= 1; i++) {
    for (let j = 0; j <= 1; j++) {
      if (
        0 > loc1Offset + i ||
        loc1Offset + i > level ||
        0 > loc2Offset + j ||
        loc2Offset + j > level
      )
        continue;
      if (loc1Offset + i === loc2Offset + j) continue;
      ans += getNumOf(composeLoc(level + 1, loc1Offset + i), composeLoc(level + 1, loc2Offset + j));
    }
  }

  ans %= 10007;

  memo[loc1][loc2] = ans;
  return ans;
}

console.log(getNumOf(0, 0));
