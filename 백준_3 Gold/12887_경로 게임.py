####231107
## 12m 49s

import sys
import heapq

M = int(input())
board = []
board.append(input())
board.append(input())

blackCnt = 0
for e in board[0]:
    if e == '#':
        blackCnt += 1
for e in board[1]:
    if e == '#':
        blackCnt += 1

PQ = []
if board[0][0] == '.':
    heapq.heappush(PQ, [1, 0, 0])
if board[1][0] == '.':
    heapq.heappush(PQ, [1, 0, 1])

visited = [[False for i in range(M)] for i in range(2)]

while True:
    curNode = heapq.heappop(PQ)
    
    if curNode[1] == M - 1:
        print(M * 2 - blackCnt - curNode[0])
        break
    
    if visited[curNode[2]][curNode[1]]:
        continue
    visited[curNode[2]][curNode[1]] = True
    
    if board[curNode[2]][curNode[1] + 1] == '.':
        heapq.heappush(PQ, [curNode[0] + 1, curNode[1] + 1, curNode[2]])
    if curNode[2] == 0  and board[1][curNode[1]] == '.':
        heapq.heappush(PQ, [curNode[0] + 1, curNode[1], 1])
    if curNode[2] == 1  and board[0][curNode[1]] == '.':
        heapq.heappush(PQ, [curNode[0] + 1, curNode[1], 0])