import sys

N, M = map(int, sys.stdin.readline().split())

graph = [[] for i in range(N + 1)]
edges = []

for i in range(1, M + 1):
  u, v = map(int, sys.stdin.readline().split())
  edges.append([u, v])
  graph[u].append([v, i])
  graph[v].append([u, i])

if N <= 2:
  print(-1)
  exit(0)

visited = [False for i in range(N + 1)]
MSTs = []

for i in range(1, N + 1):
  if visited[i]:
    continue

  queue = [[i, 0]]
  treeVertexes = [i]
  treeEdges = []
  visited[i] = True

  while len(queue) > 0:
    curNode = queue.pop(0)
    for e in graph[curNode[0]]:
      if visited[e[0]]:
        continue
      visited[e[0]] = True
      treeVertexes.append(e[0])
      treeEdges.append(e[1])
      queue.append(e)
  MSTs.append([treeVertexes, treeEdges])

if len(MSTs) > 2:
  print(-1)
  exit(0)

if len(MSTs) == 2:
  if len(MSTs[0][0]) == len(MSTs[1][0]):
    print(-1)
    exit(0)
  print(len(MSTs[0][0]), len(MSTs[1][0]))
  print(*MSTs[0][0])
  print(*MSTs[0][1])
  print(*MSTs[1][0])
  print(*MSTs[1][1])
  exit(0)

print(N - 1, 1)
print(*MSTs[0][0][:-1])
print(*MSTs[0][1][:-1])
print(MSTs[0][0][-1])
