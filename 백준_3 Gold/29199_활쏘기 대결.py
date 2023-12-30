import sys
sys.setrecursionlimit(300000)

N = int(input())
A = list(map(int, sys.stdin.readline().split()))

accumSum = A.copy()
for i in range(1, len(accumSum)):
  accumSum[i] += accumSum[i - 1]
  
memo = [[-1 for j in range(2)] for i in range(N)]

def getMaxScore(curTarget, curTurn):
  if curTarget == 0:
    res = [0, 0]
    if A[curTarget] >= 0:
      res[curTurn] = A[curTarget]
    else:
      res[(curTurn + 1) % 2] = A[curTarget]
    return res
  
  maxScore = [-float("inf"), -float("inf")]

  #맞추기
  if memo[curTarget - 1][(curTurn + 1) % 2] == -1:
    memo[curTarget - 1][(curTurn + 1) % 2] = getMaxScore(curTarget - 1, (curTurn + 1) % 2)
  res = memo[curTarget - 1][(curTurn + 1) % 2].copy()
  res[curTurn] += A[curTarget]
  if maxScore[curTurn] < res[curTurn]:
    maxScore = res
  
  #넘기기
  if memo[curTarget - 1][curTurn] == -1:
    memo[curTarget - 1][curTurn] = getMaxScore(curTarget - 1, curTurn)
  res = memo[curTarget - 1][curTurn].copy()
  res[(curTurn + 1) % 2] += A[curTarget]
  if maxScore[curTurn] < res[curTurn]:
    maxScore = res
  
  #기권
  res = [0, 0]
  res[curTurn] = 0
  res[(curTurn + 1) % 2] = accumSum[curTarget]
  if maxScore[curTurn] < res[curTurn]:
    maxScore = res
  
  return maxScore

print(getMaxScore(N - 1, 0)[0])