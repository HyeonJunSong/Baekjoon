import sys
sys.setrecursionlimit(300000)

N, M, L = map(int, sys.stdin.readline().split())

graph = [[] for i in range(N)]
for i in range(M):
  A, B, T = map(int, sys.stdin.readline().split())
  graph[A].append([B, T, -1])
  graph[B].append([A, T, -1])

visited = [False for i in range(N)]

groups = []
curGroupInd = 0

for i in range(N):
  if visited[i]:
    continue
  stack = [[i, -1]]
  groups.append([])
  
  while len(stack) > 0:
    curNode = stack.pop()
    visited[curNode[0]] = True
    groups[-1].append(curNode[0])
    
    for e in graph[curNode[0]]:
      if e[0] == curNode[1]:
        continue
      stack.append([e[0], curNode[0]])

def getDiameter(curInd, parentInd):
  
  diameter = 0
  childMax1 = 0
  childMax2 = 0
  for e in graph[curInd]:
    if e[0] == parentInd:
      continue
    
    diameter = max(diameter, getDiameter(e[0], curInd))
    
    if childMax1 < e[2]:
      childMax2 = childMax1
      childMax1 = e[2]
    elif childMax2 < e[2]:
      childMax2 = e[2]
  
  return max(diameter, childMax1 + childMax2)

def getMaxDepthOf(curInd, parentInd):

  maxDepth = 0

  for idx in range(len(graph[curInd])):
    if graph[curInd][idx][0] == parentInd:
      continue
    
    if graph[curInd][idx][2] == -1:
      graph[curInd][idx][2] = getMaxDepthOf(graph[curInd][idx][0], curInd) + graph[curInd][idx][1]
    
    maxDepth = max(maxDepth, graph[curInd][idx][2])
  
  return maxDepth

maxDepth1 = -1
maxDepth2 = -1
maxDepth3 = -1

for g in groups:
  curGroupMaxDepth = float("inf")
  
  if len(g) == 1:
    curGroupMaxDepth = 0
  elif len(g) == 2:
    curGroupMaxDepth = graph[g[0]][0][1]
  else:
    for idx in g:
      if len(graph[idx]) == 1:
        continue
      curMaxDepth = getMaxDepthOf(idx, -1)
      curGroupMaxDepth = min(curGroupMaxDepth, curMaxDepth)
    
  if maxDepth1 < curGroupMaxDepth:
    maxDepth3 = maxDepth2
    maxDepth2 = maxDepth1
    maxDepth1 = curGroupMaxDepth
  elif maxDepth2 < curGroupMaxDepth:
    maxDepth3 = maxDepth2
    maxDepth2 = curGroupMaxDepth
  elif maxDepth3 < curGroupMaxDepth:
    maxDepth3 = curGroupMaxDepth

maxDiameter = 0
for g in groups:
  curDiameter = getDiameter(g[0], -1)
  maxDiameter = max(maxDiameter, curDiameter)

if maxDepth2 == -1:
  print(maxDiameter)
elif maxDepth3 == -1:
  print(max(maxDiameter, maxDepth1 + maxDepth2 + L))
else:
  print(max(maxDiameter, maxDepth1 + maxDepth2 + L, maxDepth2 + maxDepth3 + 2 * L))