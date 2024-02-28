import sys
N, M = map(int, sys.stdin.readline().split())
Mnn2 = M//2
board = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]

accum = [[0 for j in range(N)] for i in range(N)]
ans = [[0 for j in range(N)] for i in range(N)]
for i in range(N - M + 1):
  for j in range(N - M + 1):
    
    ans[i + Mnn2][j + Mnn2] += -board[i][j] - accum[i + Mnn2 - 1][j + Mnn2] - accum[i + Mnn2][j + Mnn2 - 1] + accum[i + Mnn2 - 1][j + Mnn2 - 1]
    ans[i + Mnn2][j + Mnn2] +=                accum[max(i + Mnn2 - M, 0)][j + Mnn2] + accum[i + Mnn2][max(j + Mnn2 - M, 0)] - accum[max(i + Mnn2 - M, 0)][max(j + Mnn2 - M, 0)]
    accum[i + Mnn2][j + Mnn2] = ans[i + Mnn2][j + Mnn2] + accum[i + Mnn2 - 1][j + Mnn2] + accum[i + Mnn2][j + Mnn2 - 1] - accum[i + Mnn2 - 1][j + Mnn2 - 1]

for e in ans:
  print(*e)