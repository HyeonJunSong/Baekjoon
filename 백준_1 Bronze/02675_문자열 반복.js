const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const ans = Array(parseInt(inp[0])).fill("");
for (var i = 0; i < parseInt(inp[0]); i++) {
  inp[1 + i] = inp[1 + i].split(" ");
  for (var j = 0; j < inp[1 + i][1].length; j++)
    for (var k = 0; k < parseInt(inp[1 + i][0]); k++) ans[i] += inp[1 + i][1][j];
}

for (var i = 0; i < ans.length; i++) console.log(ans[i]);
