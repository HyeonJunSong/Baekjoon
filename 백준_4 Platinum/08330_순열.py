import sys
input = sys.stdin.readline

n = int(input())

a = [0] + list(map(int, input().split()))

cnts = [0 for i in range(n + 1)]
for i in range(n):
  cnts[min(a[i + 1], n)] += 1

for i in range(1, n + 1):
  cnts[i] += cnts[i - 1]


leafNum = 1
while leafNum < len(cnts): leafNum *= 2

segTree = [[0, 0, 0, 0] for i in range(leafNum * 2)]
for i in range(len(cnts)):
  segTree[leafNum + i][0] = i
  segTree[leafNum + i][1] = i + 1
  segTree[leafNum + i][2] = i - cnts[i]
  segTree[leafNum + i][3] = 0

for i in range(len(cnts), leafNum):
  segTree[leafNum + i][0] = i
  segTree[leafNum + i][1] = i + 1
  segTree[leafNum + i][2] = i
  segTree[leafNum + i][3] = 0

for i in range(leafNum - 1, 0, -1):
  segTree[i][0] = segTree[2 * i][0]
  segTree[i][1] = segTree[2 * i + 1][1]
  segTree[i][2] = min(segTree[2 * i][2], segTree[2 * i + 1][2])
  segTree[i][3] = 0

def segUpdate(idx, st, ed, val):
  global segTree

  if segTree[idx][0] == st and segTree[idx][1] == ed:
    segTree[idx][3] += val
    segTree[idx][2] += val
    return

  if segTree[idx][3] != 0:
    segTree[2 * idx][3] += segTree[idx][3]
    segTree[2 * idx][2] += segTree[idx][3]
    segTree[2 * idx + 1][3] += segTree[idx][3]
    segTree[2 * idx + 1][2] += segTree[idx][3]
    segTree[idx][3] = 0

  if ed <= segTree[2 * idx][1]:
    segUpdate(2 * idx, st, ed, val)
  elif st >= segTree[2 * idx + 1][0]:
    segUpdate(2 * idx + 1, st , ed, val)
  else:
    segUpdate(2 * idx, st, segTree[2 * idx][1], val)
    segUpdate(2 * idx + 1, segTree[2 * idx + 1][0] , ed, val)

  segTree[idx][2] = min(segTree[2 * idx][2], segTree[2 * idx + 1][2])

if segTree[1][2] >= 0:
  sys.stdout.write("TAK\n")
else:
  sys.stdout.write("NIE\n")

m = int(input())

for i in range(m):
  j, w = map(int, input().split())
  if a[j] < w:
    segUpdate(1, a[j], w, +1)
  elif a[j] > w:
    segUpdate(1, w, a[j], -1)

  if segTree[1][2] >= 0:
    sys.stdout.write("TAK\n")
  else:
    sys.stdout.write("NIE\n")

  a[j] = w
