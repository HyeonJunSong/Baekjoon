####231118
##1h 7m 32s

import sys

sys.setrecursionlimit(300000)

N, A, B = map(int, sys.stdin.readline().split())

scoreTable = [[0]]
for i in range(N):
    scoreTable.append([0] + list(map(int, sys.stdin.readline().split())))

AMarbles = list(map(int, sys.stdin.readline().split()))
BMarbles = list(map(int, sys.stdin.readline().split()))

memo = [[-float("inf") for j in range(len(BMarbles) + 1)] for i in range(len(AMarbles) + 1)]
def maxScore(leftInd, rightInd):
    if leftInd == len(AMarbles):
        return 0
    if rightInd == len(BMarbles):
        return 0
    
    if memo[leftInd + 1][rightInd] == -float("inf"):
        memo[leftInd + 1][rightInd] = maxScore(leftInd + 1, rightInd)
    if memo[leftInd][rightInd + 1] == -float("inf"):
        memo[leftInd][rightInd + 1] = maxScore(leftInd, rightInd + 1)
    if memo[leftInd + 1][rightInd + 1] == -float("inf"):
        memo[leftInd + 1][rightInd + 1] = maxScore(leftInd + 1, rightInd + 1)
    
    if memo[leftInd + 1][rightInd] > memo[leftInd][rightInd + 1]:
        if memo[leftInd + 1][rightInd] > memo[leftInd + 1][rightInd + 1] + scoreTable[AMarbles[leftInd]][BMarbles[rightInd]]:
            return memo[leftInd + 1][rightInd]
        else:
            return memo[leftInd + 1][rightInd + 1] + scoreTable[AMarbles[leftInd]][BMarbles[rightInd]]
    else:
        if memo[leftInd][rightInd + 1] > memo[leftInd + 1][rightInd + 1] + scoreTable[AMarbles[leftInd]][BMarbles[rightInd]]:
            return memo[leftInd][rightInd + 1]
        else:
            return memo[leftInd + 1][rightInd + 1] + scoreTable[AMarbles[leftInd]][BMarbles[rightInd]]
        
ans = maxScore(0, 0)
print(ans)

curI = 0
curJ = 0
while True:
    if curI == len(AMarbles):
        for _ in range(len(BMarbles) - curJ):
            print(2, end = " ")
        break
    if curJ == len(BMarbles):
        for _ in range(len(AMarbles) - curI):
            print(1, end = " ")
        break
    
                
    
    if memo[curI + 1][curJ] == ans:
        print(1, end = " ")
        curI += 1
    elif memo[curI][curJ + 1] == ans:
        print(2, end = " ")
        curJ += 1
    else:
        print(3, end = " ")
        ans -= scoreTable[AMarbles[curI]][BMarbles[curJ]]
        curI += 1
        curJ += 1