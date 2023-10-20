import sys

N, C = map(int, sys.stdin.readline().split())
houses = []
for i in range(N):
  houses.append(int(sys.stdin.readline()))
houses.sort()

def ifDistanceAvailalbe(dis):
  curDis = 0
  routerNum = 1
  for i in range(1, N):
    if curDis + houses[i] - houses[i - 1] >= dis:
      curDis = 0
      routerNum += 1
    else:
      curDis += houses[i] - houses[i - 1]
  
  if routerNum >= C:
    return True
  return False

st = 1
ed = (houses[-1] - houses[0]) // (C - 1)

while st <= ed:
  mid = (st + ed) // 2
  if ifDistanceAvailalbe(mid):
    st = mid + 1
  else:
    ed = mid - 1

print(ed)