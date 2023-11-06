import sys

sys.setrecursionlimit(300000)

N, K = map(int, sys.stdin.readline().split())

ans = ""
def ifPossible(curB, curC, curKLeft, curNLeft):
  global ans
  
  if curKLeft == 0:
    ans = "C" * curNLeft
    return True
  elif curKLeft < 0 or curNLeft == 0:
    return False
  
  if ifPossible(curB, curC, curKLeft - curB - curC, curNLeft - 1):
    ans += "A"
    return True

  if ifPossible(curB + 1, curC, curKLeft - curC, curNLeft - 1):
    ans += "B"
    return True

  if ifPossible(curB, curC + 1, curKLeft, curNLeft - 1):
    ans += "C"
    return True
  
  return False

if ifPossible(0, 0, K, N):
  print(ans)
else:
  print(-1)