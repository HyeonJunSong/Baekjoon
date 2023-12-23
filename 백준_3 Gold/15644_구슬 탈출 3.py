####231224
##1h 12m 56s

import sys
import heapq

N, M = map(int, sys.stdin.readline().split())
board = []
for i in range(N):
  board.append(list(input()))

def getNextPos(redI, redJ, blueI, blueJ, tilt):
  if tilt == "L":
    if redJ < blueJ:
      while redJ - 1 >= 1 and (board[redI][redJ - 1] == 'O' or (board[redI][redJ - 1] == '.')):
        redJ -= 1
        if board[redI][redJ] == 'O':
          break

      while blueJ - 1 >= 1 and (board[blueI][blueJ - 1] == 'O' or (board[blueI][blueJ - 1] == '.' and (redI != blueI or redJ != (blueJ - 1)))):
        blueJ -= 1
        if board[blueI][blueJ] == 'O':
          break

    else:
      while blueJ - 1 >= 1 and (board[blueI][blueJ - 1] == 'O' or (board[blueI][blueJ - 1] == '.')):
        blueJ -= 1
        if board[blueI][blueJ] == 'O':
          break


      while redJ - 1 >= 1 and (board[redI][redJ - 1] == 'O' or (board[redI][redJ - 1] == '.' and (blueI != redI or blueJ != (redJ - 1)))):
        redJ -= 1
        if board[redI][redJ] == 'O':
          break

        
  elif tilt == "R":
    if redJ > blueJ:
      while (redJ + 1 <= M - 2) and (board[redI][redJ + 1] == 'O' or (board[redI][redJ + 1] == '.')):
        redJ += 1
        if board[redI][redJ] == 'O':
          break
        
      while (blueJ + 1 <= M - 2) and (board[blueI][blueJ + 1] == 'O' or (board[blueI][blueJ + 1] == '.' and (redI != blueI or redJ != (blueJ + 1)))):
        blueJ += 1
        if board[blueI][blueJ] == 'O':
          break

    else:
      while (blueJ + 1 <= M - 2) and (board[blueI][blueJ + 1] == 'O' or (board[blueI][blueJ + 1] == '.')):
        blueJ += 1
        if board[blueI][blueJ] == 'O':
          break

      while (redJ + 1 <= M - 2) and (board[redI][redJ + 1] == 'O' or (board[redI][redJ + 1] == '.' and (blueI != redI or blueJ != (redJ + 1)))):
        redJ += 1
        if board[redI][redJ] == 'O':
          break

  elif tilt == "U":
    if redI < blueI:
      while redI - 1 >= 1 and (board[redI - 1][redJ] == 'O' or (board[redI - 1][redJ] == '.')):
        redI -= 1
        if board[redI][redJ] == 'O':
          break

      while blueI - 1 >= 1 and (board[blueI - 1][blueJ] == 'O' or (board[blueI - 1][blueJ] == '.' and (redI != (blueI - 1) or redJ != blueJ))):
        blueI -= 1
        if board[blueI][blueJ] == 'O':
          break
    
    else:
      while blueI - 1 >= 1 and (board[blueI - 1][blueJ] == 'O' or (board[blueI - 1][blueJ] == '.')):
        blueI -= 1
        if board[blueI][blueJ] == 'O':
          break

      while redI - 1 >= 1 and (board[redI - 1][redJ] == 'O' or (board[redI - 1][redJ] == '.' and (blueI != (redI - 1) or blueJ != redJ))):
        redI -= 1
        if board[redI][redJ] == 'O':
          break

  elif tilt == "D":
    if redI > blueI:
      while redI + 1 <= N - 2 and (board[redI + 1][redJ] == 'O' or (board[redI + 1][redJ] == '.')):
        redI += 1
        if board[redI][redJ] == 'O':
          break

      while blueI + 1 <= N - 2 and (board[blueI + 1][blueJ] == 'O' or (board[blueI + 1][blueJ] == '.' and (redI != (blueI + 1) or redJ != blueJ))):
        blueI += 1
        if board[blueI][blueJ] == 'O':
          break
    
    else:
      while blueI + 1 <= N - 2 and (board[blueI + 1][blueJ] == 'O' or (board[blueI + 1][blueJ] == '.')):
        blueI += 1
        if board[blueI][blueJ] == 'O':
          break

      while redI + 1 <= N - 2 and (board[redI + 1][redJ] == 'O' or (board[redI + 1][redJ] == '.' and (blueI != (redI + 1) or blueJ != redJ))):
        redI += 1
        if board[redI][redJ] == 'O':
          break
  
  return [[redI, redJ], [blueI, blueJ]]

redPos = [0, 0]
bluePos = [0, 0]
goalPos = [0, 0]
for i in range(N):
  for j in range(M):
    if board[i][j] == 'R':
      redPos = [i, j]
      board[i][j] = "."
    elif board[i][j] == 'B':
      bluePos = [i, j]
      board[i][j] = "."
    elif board[i][j] == 'O':
      goalPos = [i, j]


PQ = [
  [ 
    0,
    redPos,
    bluePos,
    ""
  ]
]

visited = [[[[False for j in range(M)] for i in range(N)] for j in range(M)] for i in range(N)]

res = -1
while (len(PQ) > 0):
  cur = heapq.heappop(PQ)
  
  if visited[cur[1][0]][cur[1][1]][cur[2][0]][cur[2][1]]:
    continue
  visited[cur[1][0]][cur[1][1]][cur[2][0]][cur[2][1]] = True
  
  if cur[0] >= 10:
    break
  
  for e in ["L", "R", "U", "D"]:  
    nextPos = getNextPos(cur[1][0], cur[1][1], cur[2][0], cur[2][1], e)
    if nextPos[0] == goalPos and nextPos[1] == goalPos:
      continue
    if nextPos[0] == goalPos:
      res = [cur[0] + 1, cur[3] + e]
      break
    if nextPos[1] == goalPos:
      continue
    heapq.heappush(PQ, (cur[0] + 1, nextPos[0], nextPos[1], cur[3] + e))
  
  if res != -1:
    break  

if res == -1:
  print(res)
else:
  print(*res, sep = "\n")