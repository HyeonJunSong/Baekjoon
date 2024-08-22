import sys

N = int(sys.stdin.readline())
A = [[int(sys.stdin.readline()), _] for _ in range(N)]
A.sort()

ans = 0
for i in range(N):
  ans = max(ans, A[i][1] - i + 1)

print(ans)
