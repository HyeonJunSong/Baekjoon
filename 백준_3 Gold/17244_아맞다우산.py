import sys
import queue
input = sys.stdin.readline

N, M = map(int, input().split())
house = [list(input()) for _ in range(M)]

sPoint = 0
ePoint = 0

objCnt = 0
for i in range(M):
  for j in range(N):
    if house[i][j] == 'E':
      ePoint = i * N + j
    elif house[i][j] == 'S':
      sPoint = i * N + j
    elif house[i][j] == 'X':
      house[i][j] = objCnt
      objCnt += 1

dirs = [
  [-1,  0],
  [ 0,  1],
  [ 1,  0],
  [ 0, -1]
]

visited = [[False for _ in range(1 << objCnt)] for _ in range(N * M)]

q = queue.Queue()
q.put([sPoint, 0, 0])

ans = 0

while q.not_empty:
  #꺼내기
  loc, objStatus, dis = q.get()

  #방문 처리
  if visited[loc][objStatus]: continue
  visited[loc][objStatus] = True

  #현재 상태 업데이트
  I, J = loc // N, loc % N
  if type(house[I][J]) == int:
    objStatus |= 1 << house[I][J]
  
  #종료
  if objStatus == ((1 << objCnt) - 1) and loc == ePoint:
    ans = dis
    break

  #방향 돌기
  for d in dirs:
    nxtI, nxtJ = I + d[0], J + d[1]
    if 0 > nxtI or nxtI >= M or 0 > nxtJ or nxtJ >= N: continue
    if house[nxtI][nxtJ] == '#': continue
    q.put([nxtI * N + nxtJ, objStatus, dis + 1])

print(ans)