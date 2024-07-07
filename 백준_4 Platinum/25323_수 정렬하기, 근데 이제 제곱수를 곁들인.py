import sys
import math

N = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))
sortedArr = sorted(list(map(lambda i: [arr[i], i], range(N))))

for i in range(N):
  mul = sortedArr[i][0] * arr[i]
  if math.isqrt(mul) ** 2 == mul:
    continue
  print("NO")
  exit(0)
print("YES")