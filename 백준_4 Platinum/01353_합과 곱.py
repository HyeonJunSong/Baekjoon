import math

S, P = map(int, input().split())

if S < 100 and math.e ** S < P ** math.e:
  print(-1)
  exit(0)

if S == P:
  print(1)
  exit(0)
i = 2
while S ** i < P * (i ** i) and i * math.e < S : i += 1

print(i)
