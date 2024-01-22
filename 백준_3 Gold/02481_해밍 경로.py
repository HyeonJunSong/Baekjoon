import sys
sys.setrecursionlimit(100000)

N, K = map(int, sys.stdin.readline().split())

codes = []
for i in range(N):
  curCode = sys.stdin.readline().rstrip()
  curCodeNum = 0
  for j in range(K):
    if curCode[j] == '1':
      curCodeNum += 2 ** j
  codes.append([curCodeNum, i, curCode])
codes.sort()

graph = [[] for i in range(N)]

def findNumLoc(target):
  st = 0
  ed = N - 1
  
  while st <= ed:
    mid = (st + ed) // 2
    if codes[mid][0] < target:
      st = mid + 1
    elif codes[mid][0] > target:
      ed = mid - 1
    else:
      return mid
  return -1

invTable = [2 ** i for i in range(K)]

for i in range(N):
  for j in range(K):
      if codes[i][2][j] == '0':
        target = codes[i][0] + invTable[j]
      else:
        target = codes[i][0] - invTable[j]
      
      numLoc = findNumLoc(target)
      if numLoc == -1:
        continue
      graph[i].append(numLoc)

stNode = -1
for i in range(N):
  if codes[i][1] == 0:
    stNode = i

path = [-1 for i in range(N)]

queue = [stNode]

while len(queue) > 0:
  curNode = queue.pop(0)
  
  for e in graph[curNode]:
    if path[codes[e][1]] != -1:
      continue
    path[codes[e][1]] = codes[curNode][1]
    queue.append(e)

def findPath(curNode):
  if curNode == 0:
    sys.stdout.write("%d " % 1)
    return
  findPath(path[curNode])
  sys.stdout.write("%d " % (curNode + 1))

M = int(input())
for e in range(M):
  
  cur = int(sys.stdin.readline())
  if path[cur - 1] == -1:
    print(-1)
    continue
  findPath(cur - 1)
  print()