const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const string = inp[0];
const pok = inp[1];

const stack = [];
for (let i = 0; i < string.length; i++) {
  stack.push(string[i]);

  if (stack.length < pok.length) continue;
  let ifBlowable = true;
  for (let j = 0; j < pok.length; j++) {
    if (stack[stack.length - j - 1] == pok[pok.length - j - 1]) continue;
    ifBlowable = false;
    break;
  }

  if (!ifBlowable) continue;
  for (let j = 0; j < pok.length; j++) stack.pop();
}

if (stack.length == 0) console.log("FRULA");
else console.log(stack.join(""));
