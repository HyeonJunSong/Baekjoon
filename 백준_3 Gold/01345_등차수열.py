import sys
import math

N, A0 = map(int, sys.stdin.readline().split())
if N == 0:
  print(0)
  exit(0)

S = list(map(int, sys.stdin.readline().split()))

ans = -float("INF")

for i in range(len(S)):
  if i != 0 and S[i] < S[i - 1]:
    print(-1)
    exit(0)
  ans = max(ans, (S[i] - A0) / (i + 1))

for i in range(len(S)):
  if S[i] != math.floor(A0 + (i + 1) * ans):
    print(-1)
    exit(0)
    
if ans < 0:
  print(-1)
else:
  print(ans)