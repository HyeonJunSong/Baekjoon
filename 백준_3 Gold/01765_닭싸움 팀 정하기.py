####231223
##20m 55s

import sys

n = int(input())
m = int(input())

friendOf = [[False for j in range(n + 1)] for i in range(n + 1)]
enemyOf = [[False for j in range(n + 1)] for i in range(n + 1)]
for i in range(m):
  rel, p, q = sys.stdin.readline().split()
  p, q = int(p), int(q)
  if rel == "F":
    friendOf[p][q] = True
    friendOf[q][p] = True
  else:
    enemyOf[p][q] = True
    enemyOf[q][p] = True

for i in range(1, n + 1):
  for j in range(1, n + 1):
    if enemyOf[i][j] == True:
      for k in range(1, n + 1):
        if enemyOf[j][k] == True:
          friendOf[i][k] = True
          friendOf[k][i] = True

visited = [False for i in range(n + 1)]
ans = 0

for i in range(1, n + 1):
  if visited[i]:
    continue
  ans += 1
  
  stack = [i]
  while len(stack) != 0:
    cur = stack.pop()
    if visited[cur]:
      continue
    visited[cur] = True
    for j in range(n + 1):
      if friendOf[cur][j] == True and visited[j] == False:
        stack.append(j)

print(ans)