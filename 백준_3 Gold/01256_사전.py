N, M, K = map(int, input().split())

memo = [[-1 for j in range(max(N, M) + 1)] for i in range(N + M + 1)]

def comb(n, k):
  if k == 0 or k == n: return 1
   
  if memo[n - 1][k - 1] == - 1:
    memo[n - 1][k - 1] = comb(n - 1, k - 1)
  if memo[n - 1][k] == -1:
    memo[n - 1][k] = comb(n - 1, k)
  
  return memo[n - 1][k - 1] + memo[n - 1][k]


if comb(N + M, N) < K:
  print(-1)
  exit(0)

for i in range(N + M):
  if(N == 0):
    print('z' * M)
    exit(0)

  if comb(N + M - 1, N - 1) >= K:
    print('a', end = "")
    N -= 1
  else:
    print('z', end = "")
    K -= comb(N + M - 1, N - 1)
    M -= 1
