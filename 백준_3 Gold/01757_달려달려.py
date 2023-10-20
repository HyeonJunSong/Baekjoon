####231020
##33m 08s

import sys

sys.setrecursionlimit(300000)

N, M = map(int, sys.stdin.readline().split())
D = list(map(int, sys.stdin.readlines()))

cache = [[-1 for j in range(M + 2)] for i in range(N + 1)]

def getMaxDis(curI, curM):
  
  if curI == N:
    if curM == 0:
      return 0
    else:
      return -float("INF")
  
  ans = -float("INF")
  #지금 달림
  if curM <= M and N - curI > curM:
    if cache[curI + 1][curM + 1] == -1:
      cache[curI + 1][curM + 1] = getMaxDis(curI + 1, curM + 1)
    if ans < D[curI] + cache[curI + 1][curM + 1]:
      ans = D[curI] + cache[curI + 1][curM + 1]
      
  #지금 쉼
  if curM == 0:
    if cache[curI + 1][0] == -1:
      cache[curI + 1][0] = getMaxDis(curI + 1, 0)
    if ans < cache[curI + 1][0]:
      ans = cache[curI + 1][0]
      
  elif curI + curM <= N:
    if cache[curI + curM][0] == -1:
      cache[curI + curM][0] = getMaxDis(curI + curM, 0)
    if ans < cache[curI + curM][0]:
      ans = cache[curI + curM][0]

  return ans

print(getMaxDis(0, 0))