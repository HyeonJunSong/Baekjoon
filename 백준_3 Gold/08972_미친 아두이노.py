R, C = map(int, input().split())

board = [input() for _ in range(R)]
jsLoc = []
robotsLoc = []
for i in range(R):
  for j in range(C):
    if board[i][j] == "I":
      jsLoc = [i, j]
    if board[i][j] == "R":
      robotsLoc.append([i, j])

dir = [
  [],
  [1, -1],
  [1, 0],
  [1, 1],
  [0, -1],
  [0, 0],
  [0, 1],
  [-1, -1],
  [-1, 0],
  [-1, 1]
]

js = input()

cnt = 0

nextRobotsVisited = [[0 for i in range(C)] for j in range(R)]
for e in robotsLoc:
  nextRobotsVisited[e[0]][e[1]] += 1

for e in js:

  cnt += 1
  jsLoc[0] += dir[int(e)][0]
  jsLoc[1] += dir[int(e)][1]
    
  if nextRobotsVisited[jsLoc[0]][jsLoc[1]] > 0:
      print('kraj', cnt)
      exit(0)
  
  nextRobotsLoc = []
  nextRobotsVisited = [[0 for i in range(C)] for j in range(R)]
  
  for robotLoc in robotsLoc:
    
    newRobotLoc = robotLoc.copy()
    for d in range(1, 10):
      if 0 <= robotLoc[0] + dir[d][0] and robotLoc[0] + dir[d][0] < R \
      and 0 <= robotLoc[1] + dir[d][1] and robotLoc[1] + dir[d][1] < C:
        if d == 5: continue
        if abs(jsLoc[0] - newRobotLoc[0]) + abs(jsLoc[1] - newRobotLoc[1]) > abs(jsLoc[0] - robotLoc[0] - dir[d][0]) + abs(jsLoc[1] - robotLoc[1] - dir[d][1]):
          newRobotLoc[0] = robotLoc[0] + dir[d][0]
          newRobotLoc[1] = robotLoc[1] + dir[d][1]
    
    if jsLoc == newRobotLoc:
      print('kraj', cnt)
      exit(0)

    nextRobotsLoc.append(newRobotLoc)
    nextRobotsVisited[newRobotLoc[0]][newRobotLoc[1]] += 1
  
  robotsLoc.clear()
  for nextLoc in nextRobotsLoc:
    if nextRobotsVisited[nextLoc[0]][nextLoc[1]] == 1:
      robotsLoc.append(nextLoc)

board = [['.' for j in range(C)] for i in range(R)]
board[jsLoc[0]][jsLoc[1]] = 'I'
for e in robotsLoc:
  board[e[0]][e[1]] = 'R'
for e in board:
  print(*e, sep = "")
  