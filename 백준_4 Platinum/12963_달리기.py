import sys

N, M = map(int, sys.stdin.readline().split())

city = [[] for i in range(N)]
flow = [[0 for j in range(N)] for i in range(N)]

maxSum = 0
for i in range(M):
  f, t = map(int, sys.stdin.readline().split())
  city[f].append(t)
  city[t].append(f)
  
  flow[f][t] = 3 ** i
  flow[t][f] = 3 ** i
  
  if f == N - 1 or t == N - 1:
    maxSum += 3 ** i

def checkFlow(curPath):
  
  queue = [0]
  while len(queue) > 0:
    curNode = queue.pop(0)

    if curNode == N - 1:
      return True

    for e in city[curNode]:
      if curPath[e] != -1 or flow[curNode][e] <= 0:
        continue
      
      curPath[e] = curNode
      queue.append(e)
    
  return False


def updateEdges(path):
  flowAmout = float("inf")
  pathArr = []
  curNode = N - 1
  while curNode != 0:
    pathArr.append(curNode)
    flowAmout = min(flowAmout, flow[path[curNode]][curNode])
    curNode = path[curNode]
  pathArr.append(0)
  pathArr.reverse()
  
  for i in range(len(pathArr) - 1):
    flow[pathArr[i]][pathArr[i + 1]] -= flowAmout
    flow[pathArr[i + 1]][pathArr[i]] += flowAmout
    

while True:
  curPath = [-1 for i in range(N)]
  curFlow = checkFlow(curPath)
  if not curFlow:
    break
  updateEdges(curPath)

ans = 0
for e in city[N - 1]:
  ans += flow[e][N - 1]
  ans %= 1_000_000_007

print((maxSum - ans) % 1_000_000_007)