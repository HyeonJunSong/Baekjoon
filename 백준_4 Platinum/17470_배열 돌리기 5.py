import sys

N, M, R = map(int, sys.stdin.readline().split())
arr = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]
if N < M:
  for i in range((M - N) // 2):
    arr.insert(N // 2, [0 for _ in range(M)])
  for i in range((M - N) // 2):
    arr.append([0 for _ in range(M)])
else:
  for i in range(N):
    for j in range((N - M) // 2):
      arr[i].insert(M // 2, 0)
    arr[i] += [0 for _ in range((N - M) // 2)]

symm = 0
rota = 0
loca = [0, 1, 2, 3]

for e in list(map(int, sys.stdin.readline().split())):
  if e == 1:
    symm ^= 2
    rota = (4 - rota) % 4
    loca = [loca[2], loca[3], loca[0], loca[1]]
  elif e == 2:
    symm ^= 1
    rota = (4 - rota) % 4
    loca = [loca[1], loca[0], loca[3], loca[2]]
  elif e == 3:
    rota = (rota + 1) % 4 
    loca = [loca[2], loca[0], loca[3], loca[1]]
  elif e == 4:
    rota = (rota - 1) % 4
    loca = [loca[1], loca[3], loca[0], loca[2]]
  elif e == 5:
    loca = [loca[2], loca[0], loca[3], loca[1]]
  elif e == 6:
    loca = [loca[1], loca[3], loca[0], loca[2]]

side = max(N, M)

if symm & 1 > 0:
  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + (side // 2 - j - 1)]
  arr = temp

if symm & 2 > 0:
  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + (side // 2 - i - 1)][(l & 1 > 0) * side // 2 + j]
  arr = temp


if rota == 1:
  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + j][(l & 1 > 0) * side // 2 + i]
  arr = temp

  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + (side // 2 - j - 1)]
  arr = temp


elif rota == 3:
  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + j][(l & 1 > 0) * side // 2 + i]
  arr = temp

  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + (side // 2 - i - 1)][(l & 1 > 0) * side // 2 + j]
  arr = temp

elif rota == 2:
  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + (side // 2 - j - 1)]
  arr = temp  
  
  temp = [[0 for j in range(side)] for i in range(side)]
  for l in range(4):
    for i in range(side // 2):
      for j in range(side // 2):
        temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(l & 2 > 0) * side // 2 + (side // 2 - i - 1)][(l & 1 > 0) * side // 2 + j]
  arr = temp



temp = [[0 for j in range(side)] for i in range(side)]
for l in range(4):
  for i in range(side // 2):
    for j in range(side // 2):
      temp[(l & 2 > 0) * side // 2 + i][(l & 1 > 0) * side // 2 + j] = arr[(loca[l] & 2 > 0) * side // 2 + i][(loca[l] & 1 > 0) * side // 2 + j]

for e1 in temp:
  ifPrinted = False
  for e2 in e1:
    if e2 > 0:
      print(e2, end = " ")
      ifPrinted = True
  if ifPrinted:
    print()
