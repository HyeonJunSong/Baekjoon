import sys

N = int(sys.stdin.readline())

chunGan = [list(map(int, sys.stdin.readline().split())) for _ in range(10)]
jiJi = [list(map(int, sys.stdin.readline().split())) for _ in range(12)]

def gobToIdx(gob):
  return int(gob[0]) * 12 + (ord(gob[1]) - ord('A'))

people = [[] for _ in range(120)]
for _ in range(N):
  X, S = sys.stdin.readline().split()
  people[gobToIdx(S)].append(int(X))

goongHap = [[0 for _ in range(120)] for _ in range(120)]
for i in range(120):
  for j in range(120):
    goongHap[i][j] = chunGan[i // 12][j // 12] + jiJi[i % 12][j % 12]

bestPeople = []
for i in range(120):
  bestPeople += list(map(lambda x: [i, x] ,sorted(people[i])[-3:]))

def getScore(I, J, K):
  return goongHap[bestPeople[I][0]][bestPeople[J][0]] + goongHap[bestPeople[J][0]][bestPeople[K][0]] + goongHap[bestPeople[K][0]][bestPeople[I][0]] + bestPeople[I][1] + bestPeople[J][1] + bestPeople[K][1]

ans = 0
for i in range(len(bestPeople) - 2):
  if bestPeople[i][1] == -1: continue
  for j in range(i + 1, len(bestPeople) - 1):
    if bestPeople[j][1] == -1: continue
    for k in range(j + 1, len(bestPeople)):
      if bestPeople[k][1] == -1: continue
      
      ans = max(ans, getScore(i, j, k))

print(ans)