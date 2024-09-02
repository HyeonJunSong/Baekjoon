DIV = 1000000007

N = int(input())

if N == 0:
  print(1)
  exit(0)

powNum = bin(N - 1)[2:]
powerMap = [0 for i in range(len(bin(N - 1)[2:]) + 1)]
powerMap[0] = 1
powerMap[1] = 2
for i in range(2, len(powerMap)):
  powerMap[i] = (powerMap[i - 1] ** 2) % DIV

ans = 1
for i in range(len(powNum)):
  if powNum[len(powNum) - i - 1] == '0': continue
  ans *= powerMap[i + 1]
  ans %= DIV
print(ans)