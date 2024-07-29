
R, C, N = map(int, input().split())
board = [list(input()) for _ in range(R)]

dirs = [
  [-1,  0],
  [ 1,  0],
  [ 0, -1],
  [ 0,  1],
]

firstP = [[True for j in range(C)] for i in range(R)]
for i in range(R):
  for j in range(C):
    if board[i][j] == '.': continue
    firstP[i][j] = False
    for d in dirs:
      if 0 <= i + d[0] < R and 0 <= j + d[1] < C:
        firstP[i + d[0]][j + d[1]] = False

secondP = [[True for j in range(C)] for i in range(R)]
for i in range(R):
  for j in range(C):
    if not firstP[i][j]: continue
    secondP[i][j] = False
    for d in dirs:
      if 0 <= i + d[0] < R and 0 <= j + d[1] < C:
        secondP[i + d[0]][j + d[1]] = False


if N == 0 or N == 1:
  for e in board:
    print(*e, sep="")
elif N % 4 == 2 or N % 4 == 0:
  for i in range(R):
    for j in range(C):
      print('O', end = "")
    print()
elif N % 4 == 3:
  for i in range(R):
    for j in range(C):
      if firstP[i][j]:
        print('O', end = "")
      else:
        print('.', end = "")
    print()
else:
  for i in range(R):
    for j in range(C):
      if secondP[i][j]:
        print('O', end = "")
      else:
        print('.', end = "")
    print()