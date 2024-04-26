import sys
sys.setrecursionlimit(100000)

div = 1000000009

memo = []

def getAns(n):
  
  if n == 0:
    return [0, 0]
  elif n == 1:
    return [0, 1]
  elif n == 2:
    return [1, 1]
  elif n == 3:
    return [2, 2]
  
  ans = [0, 0]
  
  for i in range(1, 4):
    if n - i < 0: break
    if memo[n - i][0] == -1:
      memo[n - i] = getAns(n - i)
    
    ans[0] = (ans[0] + memo[n - i][1]) % div
    ans[1] = (ans[1] + memo[n - i][0]) % div
  
  ans[0] %= div
  ans[1] %= div
  
  return ans


def testCase():
  global memo
  
  n = int(input())
  
  if n > len(memo):
    memo.extend([[-1, -1] for i in range(n - len(memo) + 1)])
  print(*reversed(getAns(n)), sep = " ")

T = int(input())
for t in range(T):
  testCase()