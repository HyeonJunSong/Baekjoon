const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");

const vowels = {
  a: null,
  e: null,
  i: null,
  o: null,
  u: null,
  A: null,
  E: null,
  I: null,
  O: null,
  U: null,
};

for (let i = 0; i < inp.length; i++) {
  if (inp[i].length === 1 && inp[i] === "#") break;
  console.log(
    Array.from(inp[i]).reduce((accum, val) => {
      return val in vowels ? accum + 1 : accum;
    }, 0)
  );
}
