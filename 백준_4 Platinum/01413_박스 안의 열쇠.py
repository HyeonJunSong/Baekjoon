import math

N, M = map(int, input().split())

fact = [1]
for i in range(1, N + 1):
  fact.append(fact[-1] * i)

def groupNM(n, m, maxVal):
  
  if n == 0:
    res = [0 for _ in range(N + 1)]
    res[0] += m
    return [res]
  if m == 1:
    if n > maxVal:
      return []
    res = [0 for _ in range(N + 1)]
    res[n] += 1
    return [res]
    
  
  res = []
  for i in range(maxVal, math.ceil(n / m) - 1, -1):
    curGroup = groupNM(n - i, m - 1, min(n - i, i))
    for e in curGroup:
      e[i] += 1
      res.append(e)
      
  return res

def nCr(n, r):
  if r == 0 or n == r:
    return 1
  return nCr(n - 1, r) + nCr(n - 1, r - 1)

groupRes = groupNM(N, M, N)

totCase = 0
for e in groupRes:
  curNum = 1
  curN = N
  for i in range(1, N + 1):
    if e[i] == 0:
      continue
    for j in range(e[i]):
      curNum *= nCr(curN, i)
      curNum *= fact[i - 1]
      curN -= i
    curNum //= fact[e[i]]
  totCase += curNum

allCase = fact[N]

print(totCase // math.gcd(totCase, allCase), '/', allCase // math.gcd(totCase, allCase), sep="")