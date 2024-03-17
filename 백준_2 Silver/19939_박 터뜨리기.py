import math

N, K = map(int, input().split())

a = (N - (K - 1) * K // 2) // K
if a <= 0:
  print(-1)
else:
  print(math.ceil((N - (a * K + (K - 1) * K // 2)) / (K - 1)) + K - 1)