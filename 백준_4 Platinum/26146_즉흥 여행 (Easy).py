import sys

sys.setrecursionlimit(300000)


## 필수 전역변수
# V: vertex 개수, E: edge 개수
V, E = map(int, sys.stdin.readline().split())

# 인접행렬 그래프
graph = [[] for i in range(V + 1)]
for i in range(E):
  st, ed = map(int, sys.stdin.readline().split())
  graph[st].append(ed)


groupId = 0
memberOf = []
groupIdOf = [-1 for i in range(V + 1)]

visited = [False for i in range(V + 1)]
stack = []
stackInd = [-1 for i in range(V + 1)] 


def DFS(cur):
  global groupId
  
  visited[cur] = True
  stack.append(cur)
  stackInd[cur] = len(stack)
  
  minParentInd = float("INF")
  for e in graph[cur]:
    if stackInd[e] != -1 and stackInd[e] < minParentInd:
      minParentInd = stackInd[e]
      continue
    
    if visited[e] == True:
      continue
    
    minParentInd = min(DFS(e), minParentInd)
  
  if minParentInd == stackInd[cur] or minParentInd == float("INF"):
    newSCCGroup = []
    while len(stack) > 0 and stack[-1] != cur:
      newSCCGroup.append(stack[-1])
      groupIdOf[stack[-1]] = groupId
      stackInd[stack.pop()] = -1
    newSCCGroup.append(stack[-1])
    groupIdOf[stack[-1]] = groupId
    stackInd[stack.pop()] = -1

    memberOf.append(newSCCGroup)
    groupId += 1
    
    return float("INF")
  return minParentInd

DFS(1)

for v in range(2, V + 1):
  if not visited[v]:
    print("No")
    exit(0)


if len(memberOf) == 1:
  print("Yes")
else:
  print("No")