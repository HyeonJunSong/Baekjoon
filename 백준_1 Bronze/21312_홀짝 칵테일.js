const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

let inp;
rl.on("line", (line) => {
  inp = line;
  rl.close();
});

rl.on("close", () => {
  inp = inp.split(" ").map((n) => Number(n));
  let possible = [];
  possible.push(inp[0]);
  possible.push(inp[1]);
  possible.push(inp[2]);
  possible.push(inp[0] * inp[1]);
  possible.push(inp[1] * inp[2]);
  possible.push(inp[2] * inp[0]);
  possible.push(inp[0] * inp[1] * inp[2]);

  if (possible.filter((n) => n % 2).length > 0)
    console.log(Math.max(...possible.filter((n) => n % 2)));
  else console.log(Math.max(...possible));
});
