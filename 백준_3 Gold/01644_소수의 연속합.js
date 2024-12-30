const fs = require("fs");
const inp = fs.readFileSync("/dev/stdin").toString().split("\n");
const N = parseInt(inp[0]);

if (N == 1) {
  console.log(0);
  process.exit(0);
}

const ifPrime = Array.from({ length: N + 1 }, () => true);
ifPrime[2] = true;
const primes = [];
for (let i = 2; i <= N; i++) {
  if (!ifPrime[i]) continue;
  primes.push(i);
  for (let j = 2 * i; j <= N; j += i) ifPrime[j] = false;
}

for (let i = 1; i < primes.length; i++) primes[i] += primes[i - 1];

let accumSet = new Set();
accumSet.add(0);
for (let i = 0; i < primes.length; i++) accumSet.add(primes[i]);

let ans = 0;
for (let i = 0; i < primes.length; i++) {
  if (accumSet.has(primes[i] - N)) ans++;
}

console.log(ans);
