import sys

sys.setrecursionlimit(300000)

V, E = map(int, sys.stdin.readline().split())

graph = [[] for i in range(V + 1)]
for i in range(E):
  st, ed = map(int, sys.stdin.readline().split())
  graph[st].append(ed)

groupId = 0
memberOf = []
groupIdOf = [-1 for i in range(V + 1)]

visited = [False for i in range(V + 1)]
stack = []
ifInStack = [-1 for i in range(V + 1)]

def DFS(cur):
  global groupId
  
  visited[cur] = True
  stack.append(cur)
  ifInStack[cur] = len(stack)
  
  minParentInd = float("INF")
  for e in graph[cur]:
    if ifInStack[e] != -1 and ifInStack[e] < minParentInd:
      minParentInd = ifInStack[e]
      continue
    
    if visited[e] == True:
      continue
    
    minParentInd = min(DFS(e), minParentInd)
  
  if minParentInd == ifInStack[cur] or minParentInd == float("INF"):
    newSCCGroup = []
    while len(stack) > 0 and stack[-1] != cur:
      newSCCGroup.append(stack[-1])
      groupIdOf[stack[-1]] = groupId
      ifInStack[stack.pop()] = -1
    newSCCGroup.append(stack[-1])
    groupIdOf[stack[-1]] = groupId
    ifInStack[stack.pop()] = -1

    memberOf.append(newSCCGroup)
    groupId += 1
    
    return float("INF")
  return minParentInd

for v in range(1, V + 1):
  if visited[v]:
    continue
  DFS(v)
for members in memberOf:
  members.sort()
  
memberOf.sort(key=lambda x : x[0])

print(len(memberOf))
for members in memberOf:
  print(*members, end = " ")
  print(-1)