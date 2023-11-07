
import sys

N = int(sys.stdin.readline())
L = list(map(int, sys.stdin.readline().rstrip().split()))

ans = 0

for i in range(len(L) - 1):
  ans += abs(L[i])
  L[i + 1] += L[i]

print(ans)