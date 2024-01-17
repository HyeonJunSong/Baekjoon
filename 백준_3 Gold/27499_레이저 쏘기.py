import sys

N, M, K = map(int, sys.stdin.readline().split())
sensorCords = []
for i in range(N):
  sensorCords.append(list(map(int, sys.stdin.readline().split())))

for e in sensorCords.copy():
  for i in range(1, K):
    if i % 2 == 1:
      sensorCords.append([(2 * M) * (i // 2) + M + (M - e[0]), e[1]])
    else:
      sensorCords.append([(2 * M) * (i // 2) + (e[0]), e[1]])

table = {}
for i in range(len(sensorCords)):
  curA = sensorCords[i][1] / sensorCords[i][0]
  if curA in table:
    table[curA] += 1
  else:
    table[curA] = 1

print(max(table.values()))