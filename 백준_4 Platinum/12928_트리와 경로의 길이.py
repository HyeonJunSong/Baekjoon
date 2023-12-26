import sys
sys.setrecursionlimit(300000)

N, S = list(map(int, input().split()))

comb2s = [0, 0]
curI = 2
while (curI * (curI - 1)) // 2 <= S:
  comb2s.append((curI * (curI - 1)) // 2)
  curI += 1
  
memo = [[[-1 for k in range( 2 * N - 1)] for i in range(N + 1)] for i in range(S + 1)]

def findCombinations(curS, curN, target):
  if curS <= curN and curS * 2 + (curN - curS) == target:
    return True
  
  if curS == 0 or target == curN:
    if curS == 0 and target == curN:
      return True
    return False
  
  if curS <= 0 or curN <= 0 or target <= 0:
    return False
  
  for curI in range(3, len(comb2s)):
    if comb2s[curI] > curS:
      break
    if memo[curS - comb2s[curI]][curN - 1][target - curI] == -1:
      memo[curS - comb2s[curI]][curN - 1][target - curI] = findCombinations(curS - comb2s[curI], curN - 1, target - curI)
    if memo[curS - comb2s[curI]][curN - 1][target - curI]:
      return True
  
  return False

print(int(findCombinations(S, N, 2 * N - 2)))