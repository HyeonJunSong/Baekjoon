####231031
## 20m 46s

import sys

sys.setrecursionlimit(300000)

S = input()
N = int(input())
A = []
for i in range(N):
  A.append(input())

memo = [-1 for i in range(len(S) + 1)]

def ifCanMake(st):
  
  if st == len(S):
    return 1
  
  for e in A:
    if st + len(e) <= len(S) and S.find(e, st) == st:
      if memo[st + len(e)] == -1:
        memo[st + len(e)] = ifCanMake(st + len(e))
      if memo[st + len(e)]:
        return 1
  
  return 0

print(ifCanMake(0))