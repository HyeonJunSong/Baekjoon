import sys

sys.setrecursionlimit(300000)

N = int(input())
targets = []
for i in range(N + 1):
  targets.append(list(map(int, sys.stdin.readline().split())))

def getDis(a, b):
  return abs(a[0] - b[0]) + abs(a[1] - b[1])

loc = [
  [0, 0],
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
]

memo = [[-1 for _ in range(5)] for _ in range(N + 1)]

def getMinDis(ind, curLoc):
  minDis = float("INF")
  
  if ind == N:
    return 0
  
  for d in range(5):
    if memo[ind + 1][d] == -1:
      memo[ind + 1][d] = getMinDis(ind + 1, d)
    curDis = getDis([targets[ind][0] + loc[curLoc][0], targets[ind][1] + loc[curLoc][1]], [targets[ind + 1][0] + loc[d][0], targets[ind + 1][1] + loc[d][1]]) + memo[ind + 1][d]
    if minDis > curDis:
      minDis = curDis
  
  return minDis

print(getMinDis(0, 0))