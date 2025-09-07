N, M, K = map(int, input().split())
fireballs = [list(map(int, input().split())) for _ in range(M)]

board = [[[] for j in range(N)] for i in range(N)]

for fireball in fireballs:
    board[fireball[0] - 1][fireball[1] - 1].append(fireball[2:])

dirs = [
    [-1,  0],
    [-1,  1],
    [ 0,  1],
    [ 1,  1],
    [ 1,  0],
    [ 1, -1],
    [ 0, -1],
    [-1, -1],
]

def getNxtPos(i, j, s, d):
    return (i + dirs[d][0] * s) % N, (j + dirs[d][1] * s) % N

def getCollapsedDirs(fireballs):
    firstType = fireballs[0][2] % 2
    for i in range(1, len(fireballs)):
        if fireballs[i][2] % 2 != firstType:
            return [1, 3, 5, 7]
    return [0, 2, 4, 6]

def simulate():
    global board
    # 파이어볼 이동
    nxtBoard = [[[] for j in range(1 + N)] for i in range(1 + N)]
    for i in range(N):
        for j in range(N):
            for fireball in board[i][j]:
                nxtI, nxtJ = getNxtPos(i, j, fireball[1], fireball[2])
                nxtBoard[nxtI][nxtJ].append(fireball)
    
    board = nxtBoard

    # 이동 후 액션
    for i in range(N):
        for j in range(N):
            if len(board[i][j]) <= 1: continue
            
            nxtM = sum([fireball[0] for fireball in board[i][j]]) // 5
            nxtS = sum([fireball[1] for fireball in board[i][j]]) // len(board[i][j])

            if nxtM == 0:
                board[i][j] = []
                continue

            # 합쳐진 후 방향 구하기
            collapsedDirs = getCollapsedDirs(board[i][j])
            
            newFireBalls = []
            for d in collapsedDirs:
                newFireBalls.append([nxtM, nxtS, d])
            board[i][j] = newFireBalls

    return

for _ in range(K):
    simulate()

ans = 0

for i in range(N):
    for j in range(N):
        for fireball in board[i][j]:
            ans += fireball[0]

print(ans)
