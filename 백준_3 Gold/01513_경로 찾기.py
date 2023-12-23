####231223
##25m 9s

import sys
sys.setrecursionlimit(300000)

N, M, C = map(int, sys.stdin.readline().split())
city = [[0 for j in range(M + 1)] for i in range(N + 1)]
for i in range(1, C + 1):
  iLoc, jLoc = map(int, sys.stdin.readline().split())
  city[iLoc][jLoc] = i
  
memo = [[[[-1 for l in range(C + 1)] for k in range(C + 1)] for j in range(M + 1)] for i in range(N + 1)]

def findCases(curI, curJ, curMaxOInd, ONum):
    
  if city[curI][curJ] > 0:
    if curMaxOInd > city[curI][curJ]:
      return 0

    if ONum == 0:
      return 0
    
    ONum -= 1
    curMaxOInd = city[curI][curJ]
  
  if curI == N and curJ == M:
    if ONum == 0:
      return 1
    else:
      return 0
  
  #아래
  ans = 0
  if curI + 1 <= N:
    if memo[curI + 1][curJ][curMaxOInd][ONum] == -1:
      memo[curI + 1][curJ][curMaxOInd][ONum] = findCases(curI + 1, curJ, curMaxOInd, ONum)
    ans += memo[curI + 1][curJ][curMaxOInd][ONum]
  
  #우측
  if curJ + 1 <= M:
    if memo[curI][curJ + 1][curMaxOInd][ONum] == -1:
      memo[curI][curJ + 1][curMaxOInd][ONum] = findCases(curI, curJ + 1, curMaxOInd, ONum)
    ans += memo[curI][curJ + 1][curMaxOInd][ONum]
  
  return (ans) % (1_000_007)

for i in range(0, C + 1):
  print(findCases(1, 1, 0, i), end = " ")