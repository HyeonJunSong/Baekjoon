import sys

input = sys.stdin.readline

N, K = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

lis = [[0, 0] for i in range(N)]
for i in range(N):
  lis[A[i] - 1][0] = i
  lis[B[i] - 1][1] = i
lis.sort()

ans = 0
idx = 0
while idx + K <= N:

  i = idx
  nxtIdx = idx + K
  while i < nxtIdx:
    nxtIdx = max(nxtIdx, lis[i][1] + 1)
    i += 1
  
  idx = nxtIdx
  ans += 1

print(ans)