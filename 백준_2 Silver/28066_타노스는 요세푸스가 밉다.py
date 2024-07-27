N, K = map(int, input().split())

cLeft = N
curSt = 0

curCs = [True for _ in range(N)]

while cLeft >= K:
  curSt = (curSt + 1) % N
  cnt = 0
  while cnt < K - 1:
    if not curCs[curSt]:
      curSt = (curSt + 1) % N
      continue
    curCs[curSt] = False
    curSt = (curSt + 1) % N
    cnt += 1
  
  while not curCs[curSt]:
    curSt = (curSt + 1) % N
  
  cLeft -= (K - 1)

print(curSt + 1)