####23.10.21
## 22m 31s

import sys

n, m = map(int, sys.stdin.readline().split())
c1, c2 = map(int, sys.stdin.readline().split())
P = list(map(int, sys.stdin.readline().split()))
Q = sorted(list(map(int, sys.stdin.readline().split())))


def findLoc(val):
  st = 0
  ed = len(Q) - 1
  
  while st <= ed:
    mid = (st + ed) // 2
    if Q[mid] <= val:
      st = mid + 1
    else:
      ed = mid - 1
  
  return ed

ans = float("INF")
ansCnt = 0

for p in P:
  res = findLoc(p)
  if res == len(Q) - 1:
    if ans > abs(p - Q[res]):
      ans = abs(p - Q[res])
      ansCnt = 1
    elif ans == abs(p - Q[res]):
      ansCnt += 1
  elif res == -1:
    if ans > abs(p - Q[0]):
      ans = abs(p - Q[0])
      ansCnt = 1
    elif ans == abs(p - Q[0]):
      ansCnt += 1
  else:
    if abs(p - Q[res]) == abs(p - Q[res + 1]):
      if ans > abs(p - Q[res]):
        ans = abs(p - Q[res])
        ansCnt = 2
      elif ans == abs(p - Q[res]):
        ansCnt += 2    
    else:
      curMin = min(abs(p - Q[res]), abs(p - Q[res + 1]))
      if ans > curMin:
        ans = curMin
        ansCnt = 1
      elif ans == curMin:
        ansCnt += 1

print(ans + abs(c1 - c2), ansCnt)