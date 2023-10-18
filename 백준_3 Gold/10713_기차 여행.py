#### 231018
## 55m 18s

import sys

sys.setrecursionlimit(10000)

N, M = map(int, sys.stdin.readline().split())
Parr = list(map(int, sys.stdin.readline().split()))
A = [0 for _ in range(N)]
B = [0 for _ in range(N)]
C = [0 for _ in range(N)]

for i in range(N - 1):
  A[i + 1], B[i + 1], C[i + 1] = map(int, sys.stdin.readline().split()) 

#### 철도 i를 몇번 씩 타는지 체크
leafSize = 1
while leafSize < N:
  leafSize *= 2

numRail = [[0, 0, 0] for _ in range(leafSize * 2)]
for i in range(leafSize):
  numRail[leafSize + i][1] = i + 1
  numRail[leafSize + i][2] = i + 2

for i in range(leafSize - 1, 0, -1):
  numRail[i][1] = numRail[2 * i][1]
  numRail[i][2] = numRail[2 * i + 1][2]

def update(st, ed, val, ind):
  if numRail[ind][1] == st and numRail[ind][2] == ed:
    numRail[ind][0] += val
    return
  
  if numRail[ind][0] > 0:
    numRail[2 * ind][0] += numRail[ind][0]
    numRail[2 * ind + 1][0] += numRail[ind][0]
    numRail[ind][0] = 0
  
  if numRail[2 * ind][2] >= ed:      
    return update(st, ed, val, 2 * ind)
  elif numRail[2 * ind + 1][1] <= st:
    return update(st, ed, val, 2 * ind + 1)
  
  update(st, numRail[2 * ind][2], val, 2 * ind)
  update(numRail[2 * ind + 1][1], ed, val, 2 * ind + 1)

def getVal(st, ed, ind):
  if numRail[ind][1] == st and numRail[ind][2] == ed:
    return numRail[ind][0]
  
  if numRail[ind][0] > 0:
    numRail[2 * ind][0] += numRail[ind][0]
    numRail[2 * ind + 1][0] += numRail[ind][0]
    numRail[ind][0] = 0
  
  if numRail[2 * ind][2] >= ed:
    return getVal(st, ed, 2 * ind)
  elif numRail[2 * ind + 1][1] <= st:
    return getVal(st, ed, 2 * ind + 1)

for i in range(len(Parr) - 1):
  if Parr[i + 1] < Parr[i]:
    update(Parr[i + 1], Parr[i], 1, 1)
  else:
    update(Parr[i], Parr[i + 1], 1, 1)

totPrice = 0
for i in range(N - 1):
  getVisitNum = getVal(i + 1, i + 2, 1)
  if getVisitNum == 0:
    continue
  
  totPrice += min(getVisitNum * B[i + 1] + C[i + 1], getVisitNum * A[i + 1])

print(totPrice)