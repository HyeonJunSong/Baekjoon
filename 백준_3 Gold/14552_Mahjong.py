import sys

sys.setrecursionlimit(300000)

hands = list(map(int, sys.stdin.readline().split()))

handsNum = [0 for i in range(10)]
for i in hands:
  handsNum[i] += 1
  
ans = set()
## 머리 7개 가능한지
def ifPossible_twoHead(curHandsNum):
  for i in curHandsNum:
    if i != 0 and i != 2:
      return False
  return True

def ifPossible_withBody(curHandsNum, ind):
  if sum(curHandsNum) == 0:
    return True
    
  if ind == 10:
      return False

  if curHandsNum[ind] >= 3:
    nex = curHandsNum.copy()
    nex[ind] -= 3
    if ifPossible_withBody(nex, ind):
      return True

  if ind >= 8:
    return ifPossible_withBody(curHandsNum, ind + 1)

  while curHandsNum[ind] > 0 and curHandsNum[ind + 1] > 0 and curHandsNum[ind + 2] > 0:
    curHandsNum[ind] -= 1
    curHandsNum[ind + 1] -= 1
    curHandsNum[ind + 2] -= 1
    
  if curHandsNum[ind] > 0:
    return False
  
  return ifPossible_withBody(curHandsNum, ind + 1)

for i in range(1, 10):
  if handsNum[i] == 4:
    continue
  
  curHandsNum = handsNum.copy()
  curHandsNum[i] += 1
  
  if ifPossible_twoHead(curHandsNum):
    ans.add(i)
    continue
  
  for j in range(1, 10):
    curHandsNum2 = curHandsNum.copy()
    if curHandsNum2[j] < 2:
      continue
    curHandsNum2[j] -= 2
    if ifPossible_withBody(curHandsNum2, 1):
      ans.add(i)
      break

if len(ans) == 0:
  print(-1)
else:
  print(*sorted(list(ans)))