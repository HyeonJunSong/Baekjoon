####231122
##37m 36s

import sys
sys.setrecursionlimit(300000)

n, k =  map(int, sys.stdin.readline().split())
ban = [False for i in range(n + 1)]
for e in list(map(int, sys.stdin.readline().split())):
  ban[e] = True

memo = [-1 for i in range(n + 2)]

def findAns(curNum):
  
  winnable = False  
  minAns = float("inf")
  maxAns = 0
  for next in range(curNum, min(curNum + k, n + 1)):
    if ban[next]:
      continue
    
    if memo[next + 1] == -1:
      memo[next + 1] = findAns(next + 1)
    
    if not memo[next + 1][0]:
      winnable = True
      if minAns > memo[next + 1][1] + 1:
        minAns = memo[next + 1][1] + 1

    if maxAns < memo[next + 1][1] + 1:
      maxAns = memo[next + 1][1] + 1
  
  if winnable:
    return [True, minAns]
  else:
    return [False, maxAns]

print(findAns(1)[1])