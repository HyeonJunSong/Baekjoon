const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

let idx = 0;
let T = parseInt(inp[idx++]);

function solve() {
  const nums = inp[idx++];

  let cnt = 1;
  let num = nums[0];
  const ans = [];

  for (let i = 1; i < nums.length; i++) {
    if (nums[i - 1] !== nums[i]) {
      ans.push(cnt);
      ans.push(num);
      cnt = 1;
      num = nums[i];
    } else {
      cnt++;
    }
  }
  ans.push(cnt);
  ans.push(num);
  console.log(ans.join(""));
}

while (T--) solve();
