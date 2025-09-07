
N, M = map(int, input().split())
board = [input() for _ in range(N)]

visited = [[0 for j in range(M)] for i in range(N)]

dirMap = {
    'U' : [-1,  0],
    'D' : [ 1,  0],
    'L' : [ 0, -1],
    'R' : [ 0,  1],
}

ans = 0

def findCycleOrEnd(i, j, path):
    if 0 > i or i >= N or 0 > j or j >= M: return [[i, j]]

    if visited[i][j] == 2: return []
    if visited[i][j] == 1:
        cycle = [[i, j]]
        while path[-1][0] != i or path[-1][1] != j:
            cycle.append(path.pop())
        return cycle

    visited[i][j] = 1
    path.append([i, j])
    curD = dirMap[board[i][j]]
    cycle = findCycleOrEnd(i + curD[0], j + curD[1], path)
    visited[i][j] = 2

    return cycle

ans = 0
for i in range(N):
    for j in range(M):
        if visited[i][j] == 2: continue
        curCycle = findCycleOrEnd(i, j, [])

        if len(curCycle) > 0:
            ans += 1

print(ans)