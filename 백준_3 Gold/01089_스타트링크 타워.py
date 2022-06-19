
#각 인덱스에 해당하는 숫자를 만들때 켜져있으면 안되는 좌표들
impossibleNum = [
    [ [1, 1], [2, 1], [3, 1] ],
    [ [0, 0], [0, 1], [1, 0], [1, 1], [2, 0], [2, 1], [3, 0], [3, 1], [4, 0], [4, 1] ],
    [ [1, 0], [1, 1], [3, 1], [3, 2] ],
    [ [1, 0], [1, 1], [3, 0], [3, 1] ],
    [ [0, 1], [1, 1], [3, 0], [3, 1], [4, 0], [4, 1] ],
    [ [1, 1], [1, 2], [3, 0], [3, 1] ],
    [ [1, 1], [1, 2], [3, 1] ],
    [ [1, 0], [1, 1], [2, 0], [2, 1], [3, 0], [3, 1], [4, 0], [4, 1] ],
    [ [1, 1], [3, 1] ],
    [ [1, 1], [3, 0], [3, 1] ],
]

N = int(input())

lightBoard = []

for i in range(5):
    lightBoard.append(input())

#전광판의 자릿수마다 만들 수 있는 숫자들
floor = []

ifCannot = False

for i in range(N):
    curFloorList = []
    for j in range(10):
        ifTrue = True
        for k in range(len(impossibleNum[j])):
            if lightBoard[impossibleNum[j][k][0]][ 4 * i + impossibleNum[j][k][1]] == '#':
                ifTrue = False
                break
        if ifTrue:
            curFloorList.append(j)

    if len(curFloorList) == 0:
        ifCannot = True
        break
    floor.append(curFloorList)

if ifCannot:
    print(-1)
else:

    befSum = 0
    for i in range(len(floor[-1])):
        befSum += floor[-1][i]
    befCnt = len(floor[-1])

    for i in range(N-2, -1, -1):
        curSum = 0
        for j in range(len(floor[i])):
            curSum += floor[i][j]
        befSum = curSum * befCnt * (10 ** (N - i - 1)) + len(floor[i]) * befSum
        befCnt *= len(floor[i])

    print("%.5f" % (befSum / befCnt))