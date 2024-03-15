
N = int(input())

pattern = [
  [4, 1, 7],
  [0, 6],
  [5],
  [4],
  [3, 0],
  [2],
  [1],
  [0]
]

memo = [[-1 for j in range(8)] for i in range(N + 1)]

def getAns(idx, curLinePattern):
  if idx == N - 1:
    if curLinePattern == 7 or curLinePattern == 1 or curLinePattern == 4:
      return 1
    else:
      return 0
  
  ans = 0
  for e in pattern[curLinePattern]:
    if memo[idx + 1][e] == -1:
      memo[idx + 1][e] = getAns(idx + 1, e)
    ans += memo[idx + 1][e]
  return ans

print(getAns(0, 0))