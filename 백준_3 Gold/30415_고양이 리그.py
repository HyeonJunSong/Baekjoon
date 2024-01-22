import sys
import math

#720720

n, m = map(int, sys.stdin.readline().split())

divisors = []
for i in range(2, math.isqrt(n)):
  if n % i == 0:
    divisors.append(i)
    divisors.append(n // i)

if math.isqrt(n) != 1:
  if math.isqrt(n) ** 2 == n:
    divisors.append(math.isqrt(n))
  else:
    if n % math.isqrt(n) == 0:
      divisors.append(math.isqrt(n))
      divisors.append(n // math.isqrt(n))

divisors.sort()

graph = [[False for j in range(len(divisors))] for i in range(len(divisors))]
for i in range(len(divisors) - 1):
  for j in range(i + 1, len(divisors)):
    if math.lcm(divisors[i], divisors[j]) == n:
      graph[i][j] = True
      graph[j][i] = True

ansList = []
curList = []
ansSum = float("inf")
def findAns(curInd, m, curSum):
  global ansSum, ansList
  if curSum >= ansSum:
    return False
  if m == 0:
    if ansSum > curSum:
      ansSum = curSum
      ansList = curList.copy()
    return True
  if curInd == len(divisors):
    return False
  
  ifPossible = True
  res = False
  for e in curList:
    if not graph[curInd][e]:
      ifPossible = False
      break
  if ifPossible:
    curList.append(curInd)
    res = findAns(curInd + 1, m - 1, curSum + divisors[curInd])
    curList.pop()

  res = findAns(curInd + 1, m, curSum) or res

  return res

if findAns(0, m, 0):
  for e in ansList:
    sys.stdout.write("%d " % divisors[e])
else:
  print(-1)