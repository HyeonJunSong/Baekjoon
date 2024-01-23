import sys
import itertools
import heapq

N = int(sys.stdin.readline())
A = list(map(int, sys.stdin.readline().split()))
M = int(sys.stdin.readline())
controls = []
for i in range(M):
  l, r, c = map(int, sys.stdin.readline().split())
  controls.append([l - 1, r - 1, c])

permutations = list(itertools.permutations([i for i in range(N)], N))

def arrToNum(arr):
  num = 0
  for i in range(N):
    num += (N ** i) * arr[i]
  return num

def numToArr(num):
  arr = []
  for i in range(N):
    arr.append(num % N)
    num //= N
  return arr

def ifAscending(arr):
  for i in range(N - 1):
    if A[arr[i]] > A[arr[i + 1]]:
      return False
  return True

PQ = [[0, arrToNum([i for i in range(N)])]]

visited = [False for i in range(N ** N)]

ans = -1

while len(PQ) > 0:
  curNode = heapq.heappop(PQ)
  
  if visited[curNode[1]]:
    continue
  visited[curNode[1]] = True
  
  curList = numToArr(curNode[1])
  if ifAscending(curList):
    ans = curNode[0]
    break
  
  for e in controls:
    nexList = curList.copy()
    nexList[e[0]], nexList[e[1]] = nexList[e[1]], nexList[e[0]]
    nexNum = arrToNum(nexList)
    
    if visited[nexNum]:
      continue
    heapq.heappush(PQ, [curNode[0] + e[2], nexNum])

print(ans)