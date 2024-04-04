
(N, D) = map(int, input().split())

shortCuts = []
for i in range(N):
  curInput = list(map(int, input().split()))
  if curInput[0] > D or curInput[1] > D:
    continue
  shortCuts.append(curInput)
N = len(shortCuts)

shortCuts.sort(key= lambda x: x[0])

cache = [-1 for i in range(N)]

def retShortestWayCost(ind : int):
  
  shortestWayCost = (D - shortCuts[ind][1]) + shortCuts[ind][2]
  
  nextShortCutInd = ind + 1
  while nextShortCutInd < N and shortCuts[nextShortCutInd][0] < shortCuts[ind][1]:
    nextShortCutInd += 1
  
  for i in range(nextShortCutInd, N):
    if cache[i] == -1:
      cache[i] = retShortestWayCost(i)
    if shortestWayCost > (shortCuts[i][0] - shortCuts[ind][1]) + cache[i] + shortCuts[ind][2]:
      shortestWayCost = (shortCuts[i][0] - shortCuts[ind][1]) + cache[i] + shortCuts[ind][2]
  
  return shortestWayCost

totShortestWayCost = D
for i in range(N):
  if cache[i] == -1:
    cache[i] = retShortestWayCost(i)
  if totShortestWayCost > shortCuts[i][0] + cache[i]:
    totShortestWayCost = shortCuts[i][0] + cache[i]

print(totShortestWayCost)