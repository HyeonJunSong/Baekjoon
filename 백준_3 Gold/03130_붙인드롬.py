
N, M = map(int, input().split())

palSize = N // 2
leftPals = []
def getLeftPal(curNum, idx):
  global leftPals
  if palSize - idx - 1 - idx == 0:
    if idx == 0:
      for i in range(1, 10):
        leftPals.append(i)
    else:
      for i in range(10):
        leftPals.append(curNum + i * (10 ** idx))
    return
  elif palSize - idx - 1 < idx:
    leftPals.append(curNum)
    return

  if idx == 0:
    for i in range(1, 10):
      getLeftPal(curNum + i * (10 ** idx) + i * (10 ** (palSize - idx - 1)), idx + 1)
  else:
    for i in range(10):
      getLeftPal(curNum + i * (10 ** idx) + i * (10 ** (palSize - idx - 1)), idx + 1)

numCnt = [0 for i in range(M)]
def getRightPal(curNum, idx):
  global leftPals
  if palSize - idx - 1 - idx == 0:
    for i in range(10):
      numCnt[(curNum + i * (10 ** idx)) % M] += 1
    return
  elif palSize - idx - 1 < idx:
    numCnt[curNum % M] += 1
    return

  for i in range(10):
    getRightPal(curNum + i * (10 ** idx) + i * (10 ** (palSize - idx - 1)), idx + 1)

getLeftPal(0, 0)
getRightPal(0, 0)
ans = 0
for e in leftPals:
  c = (e * (10 ** palSize)) % M
  if c == 0:
    ans += numCnt[0]
  else:
    ans += numCnt[M - c]
print(ans)