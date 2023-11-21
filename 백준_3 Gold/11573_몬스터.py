####231121
##42m 59s

import sys
sys.setrecursionlimit(300000)

memo = [[[-1 for k in range(101)] for j in range(101)] for i in range(101)]
def findPossibility(r, y, b):
  if r == 0 and y == 0:
    return [0, 0, 1]
  if y == 0 and b == 0:
    return [1, 0, 0]
  if b == 0 and r == 0:
    return [0, 1, 0]
  
  tot = r * y + y * b + b * r
  curPossibility = [0, 0, 0]
  if r > 0 and y > 0:
    if memo[r][y - 1][b] == -1:
      memo[r][y - 1][b] = findPossibility(r, y - 1, b)
    curPossibility[0] += memo[r][y - 1][b][0] * r * y / tot
    curPossibility[1] += memo[r][y - 1][b][1] * r * y / tot
    curPossibility[2] += memo[r][y - 1][b][2] * r * y / tot
  
  if y > 0 and b > 0:
    if memo[r][y][b - 1] == -1:
      memo[r][y][b - 1] = findPossibility(r, y, b - 1)
    curPossibility[0] += memo[r][y][b - 1][0] * y * b / tot
    curPossibility[1] += memo[r][y][b - 1][1] * y * b / tot
    curPossibility[2] += memo[r][y][b - 1][2] * y * b / tot
  
  if b > 0 and r > 0:
    if memo[r - 1][y][b] == -1:
      memo[r - 1][y][b] = findPossibility(r - 1, y, b)
    curPossibility[0] += memo[r - 1][y][b][0] * b * r / tot
    curPossibility[1] += memo[r - 1][y][b][1] * b * r / tot
    curPossibility[2] += memo[r - 1][y][b][2] * b * r / tot
  
  return curPossibility

def testCase():
  r, y, b = map(int, sys.stdin.readline().split())
  print(*findPossibility(r, y, b))

T = int(input())
for _ in range(T):
  testCase()