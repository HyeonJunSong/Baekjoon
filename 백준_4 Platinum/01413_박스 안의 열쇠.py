import math

N, M = map(int, input().split())

fact = [1]
for i in range(1, N + 1):
  fact.append(fact[-1] * i)

print(fact)

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

groupRes = groupNM(N, M)

for e in groupRes:
  curNum = 1
  for i in range(N + 1):
    