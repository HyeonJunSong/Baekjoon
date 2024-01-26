import sys
sys.setrecursionlimit(100000)
N, K = map(int, input().split())
dp = [[float("inf") for j in range(N + 1)] for i in range(K + 1)]
dp[1] = [i for i in range(N + 1)]

for k in range(2, K + 1):
  dp[k][1] = 1
  dp[k][2] = 2
  for n in range(3, N + 1):
    for i in range(1, n - 1):
      if max(dp[k - 1][i], dp[k][n - 1 - i]) + 1 > dp[k][n]:
        break
      dp[k][n] = max(dp[k - 1][i], dp[k][n - 1 - i]) + 1

print(dp[K][N])