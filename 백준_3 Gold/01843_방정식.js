const fs = require("fs");
const N = parseInt(fs.readFileSync("/dev/stdin"));

//A
console.log(
  parseInt((N - 1) / 2) * (parseInt((N - 1) / 2) + 1) - (N % 2 == 1 ? parseInt((N - 1) / 2) : 0)
);

//B
const divisors = [];
for (let i = 1; i < N ** 0.5; i++) if (N % i == 0) divisors.push(i, N / i);
if (parseInt(N ** 0.5) ** 2 === N) divisors.push(N ** 0.5);
divisors.sort((a, b) => a - b);

let bAns = 0;
for (let i = 0; i < divisors.length; i++) {
  for (let j = i; j < divisors.length; j++) {
    let st = j;
    let ed = divisors.length - 1;
    const target = divisors[i] + divisors[j];
    while (st <= ed) {
      const mid = (st + ed) >> 1;
      if (divisors[mid] < target) st = mid + 1;
      else ed = mid - 1;
    }
    if (st < divisors.length && target === divisors[st]) bAns++;
  }
}
console.log(bAns);

//C

const ifPrime = Array.from({ length: N + 1 }, () => true);
for (let i = 2; i <= N; i++) {
  if (!ifPrime[i]) continue;
  for (let j = 2 * i; j <= N; j += i) ifPrime[j] = false;
}

const primes = [];
for (let i = 2; i <= N; i++) if (ifPrime[i]) primes.push(i);

let cAns = 0;

for (let i = 0; i < primes.length; i++)
  for (let j = i; j < primes.length; j++)
    if (primes[i] + primes[j] <= N && ifPrime[primes[i] + primes[j]]) cAns++;

console.log(cAns);
