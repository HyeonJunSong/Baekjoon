const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const n = parseInt(inp);

const ans = [];

function getStackArray(curN, stack, res) {
  if (curN == n + 1) {
    ans.push([...res, ...stack.slice().reverse()]);
    return;
  }
  if (stack.length > 0) {
    res.push(stack.pop());
    getStackArray(curN, stack, res);
    stack.push(res.pop());
  }
  if (curN <= n) {
    stack.push(curN);
    getStackArray(curN + 1, stack, res);
    stack.pop();
  }
}

getStackArray(1, [], []);

ans.sort((a, b) => {
  for (let i = 0; i < a.length; i++) {
    if (a[i] == b[i]) continue;
    return a[i] - b[i] > 0;
  }
});

for (let i = 0; i < ans.length; i++) console.log(...ans[i]);
