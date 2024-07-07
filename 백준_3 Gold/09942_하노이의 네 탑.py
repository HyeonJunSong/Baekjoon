import sys

memo = [-1 for _ in range(1000)]
def getAns(n):
  if n == 0 or n == 1:
    return n
  
  ans = float("inf")
  for k in range(1, n):
    if memo[k] == -1:
      memo[k] =  getAns(k)
    ans = min(ans, 2 * (memo[k] + 2 ** (n - 1 - k) - 1) + 1)
  return ans

inp = sys.stdin.readlines()
for i in range(len(inp)):
  n = int(inp[i])
  print("Case %d: %d" % (i + 1, getAns(n)))