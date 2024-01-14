import sys
sys.setrecursionlimit(300000)

N = int(input())
K = int(input())
K -= 1

memo = [[[[-1 for l in range(2)] for k in range(2)] for j in range(2)] for i in range(N + 1)]
def getNumOfCases(curN, ifPrevEmpty, ifCurEmpty, ifFreeEmpty):
  if curN == N:
    return 1
  
  if memo[curN][ifPrevEmpty][ifCurEmpty][ifFreeEmpty] != -1:
    return memo[curN][ifPrevEmpty][ifCurEmpty][ifFreeEmpty]
    
  if curN == K:
    memo[curN][ifPrevEmpty][ifCurEmpty][ifFreeEmpty] = getNumOfCases(curN + 1, 0, 1, ifFreeEmpty)
    return memo[curN][ifPrevEmpty][ifCurEmpty][ifFreeEmpty]
  
  numOfCases = 0
  
  if ifPrevEmpty:
    numOfCases += getNumOfCases(curN + 1, ifCurEmpty, 1, ifFreeEmpty)
  
  if ifCurEmpty:
    numOfCases += getNumOfCases(curN + 1, 0, 1, ifFreeEmpty)
  
  if curN + 1 != K and curN < N - 1:
    numOfCases += getNumOfCases(curN + 1, ifCurEmpty, 0, ifFreeEmpty)
  
  if ifFreeEmpty:
    numOfCases += getNumOfCases(curN + 1, ifCurEmpty, 1, 0)
    
  memo[curN][ifPrevEmpty][ifCurEmpty][ifFreeEmpty] = numOfCases
  return numOfCases

print(getNumOfCases(0, 0, 1, 1))