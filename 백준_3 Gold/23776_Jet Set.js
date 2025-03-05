const fs = require("fs");
const inp = fs
  .readFileSync("/dev/stdin")
  .toString()
  .split("\n")
  .map((v) => v.split(" ").map((v) => parseInt(v)));

const [n] = inp[0];
const coords = inp.slice(1, n + 1).map((v) => (v[1] + 180) * 2);
coords.push(coords[0]);

const visited = Array.from({ length: 720 }, () => false);
for (let i = 0; i < n; i++) {
  if (Math.abs(coords[i] - coords[i + 1]) < 360) {
    const st = Math.min(coords[i], coords[i + 1]);
    const ed = Math.max(coords[i], coords[i + 1]);
    for (let j = st; j <= ed; j++) visited[j] = true;
  } else if (Math.abs(coords[i] - coords[i + 1]) > 360) {
    const st = Math.max(coords[i], coords[i + 1]);
    const ed = Math.min(coords[i], coords[i + 1]) + 720;
    for (let j = st; j <= ed; j++) visited[j % 720] = true;
  } else {
    for (let j = 0; j < 720; j++) visited[j] = true;
  }
}

for (let j = 0; j < 720; j++) {
  if (visited[j]) continue;

  if (j % 2 == 0) console.log(`no ${j / 2 - 180}.0`);
  else console.log(`no ${j / 2 - 180}`);
  process.exit(0);
}

console.log("yes");
