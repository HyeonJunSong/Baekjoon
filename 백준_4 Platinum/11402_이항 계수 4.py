import sys

sys.setrecursionlimit(300000)

N, K, M = map(int, sys.stdin.readline().split())


def getAns(N, K):
  if N >= M or K >= M:
  
    if N % M < K % M:
      print(0)
      exit(0)

    curEnd = getAns(N // M, K // M)
    return (nCr(N % M, K % M) * curEnd) % M
  else:
    return nCr(N % M, K % M) % M

cache = [[-1 for i in range(M + 1)] for j in range(M + 1)]

def nCr(n, r):
  if n == r or r == 0:
    return 1
  if cache[n - 1][r - 1] == -1:
    cache[n - 1][r - 1] = nCr(n - 1, r - 1)
  if cache[n - 1][r] == -1:
    cache[n - 1][r] = nCr(n - 1, r)
  return (cache[n - 1][r - 1] + cache[n - 1][r]) % M

print(getAns(N, K))

# for i in range(0, 100):
#   print("%2d" % i, " ", end = "")
#   for j in range(0, i + 1):
#     print("%2d"% nCr(i, j, 1), end = " ")
#   print()