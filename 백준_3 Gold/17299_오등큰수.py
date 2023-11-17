import sys
N = int(input())
A = list(map(int, sys.stdin.readline().rstrip().split()))

## 각 숫자별로 몇번 등장하는지 매핑.
appearNum = [0 for i in range(1000001)]
for e in A:
  appearNum[e] += 1

## 각 등장횟수별로 인덱스와 숫자 저장
appearIndexes = {}
for i in range(N):
  if appearNum[A[i]] in appearIndexes:
    appearIndexes[appearNum[A[i]]].append(i)
  else:
    appearIndexes[appearNum[A[i]]] = [i]
    
ans = [-1 for i in range(N)]

curIndexList = []
def findMinInd(target):
  st = 0
  ed = len(curIndexList) - 1
  
  while st <= ed:
    mid = (st + ed) // 2
    
    if curIndexList[mid] <= target:
      st = mid + 1
    else:
      ed = mid - 1
  
  if st == len(curIndexList):
    return -1
  else:
    return st

for e in sorted(list(appearIndexes), reverse=True):
  for ind in appearIndexes[e]:
    curAns = findMinInd(ind)
    if curAns != -1:
      ans[ind] = A[curIndexList[curAns]]
  curIndexList += appearIndexes[e]
  curIndexList.sort()

print(*ans)