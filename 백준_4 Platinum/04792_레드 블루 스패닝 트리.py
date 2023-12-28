import sys

n, m, k = 0, 0, 0
graph = []

def findMinBlue():
  
  visited = [False for i in range(n + 1)]
  cnt = 0
  for i in range(1, n + 1):
    if visited[i]:
      continue

    cnt += 1
    
    stack = [i]
    while len(stack) != 0:
      cur = stack.pop()

      if visited[cur]:
        continue
      visited[cur] = True
      
      for e in graph[cur]:
        if visited[e[0]]:
          continue
        if e[1] == 'R':
          stack.append(e[0])
  
  return cnt - 1

def findMaxBlue():
  
  visited = [False for i in range(n + 1)]
  cnt = 0
  for i in range(1, n + 1):
    if visited[i]:
      continue

    cnt += 1
    
    stack = [i]
    while len(stack) != 0:
      cur = stack.pop()
      
      if visited[cur]:
        continue
      visited[cur] = True
      
      for e in graph[cur]:
        if visited[e[0]]:
          continue
        if e[1] == 'B':
          stack.append(e[0])
  
  return n - cnt

def testCase():
  global graph, n, m, k
  
  n, m, k = map(int, sys.stdin.readline().split())
  if n == 0:
    return 1
  
  graph = [[] for i in range(n + 1)]
  for i in range(m):
    c, f, t = sys.stdin.readline().split()
    f = int(f)
    t = int(t)

    graph[f].append([t, c])
    graph[t].append([f, c])
  
  blueRange = [findMinBlue(), findMaxBlue()]
  
  if blueRange[0] <= k <= blueRange[1]:
    print(1)
  else:
    print(0)
  
  
  return 0

while testCase() == 0:
  pass