cards = [[], [], [], []]
index = [0, 0, 0, 0]

def getLargestDim():

    maxIncreaseVolume = 0
    maxIncVolInd = -1
    
    for i in range(4):
        if len(cards[i]) == index[i]:
            continue

        curVolIncrease = cards[i][index[i]]
        for j in range(4):
            if j == i:
                continue;
            curVolIncrease *= hyperCube[j]

        if maxIncreaseVolume < curVolIncrease:
            maxIncreaseVolume = curVolIncrease
            maxIncVolInd = i
    
    return maxIncVolInd

N, K = map(int, input().split(' '))
hyperCube = list(map(int, input().split(' ')))

for i in range(N):
    T, U = input().split()
    cards[ord(T) - ord('A')].append(int(U));

for i in range(4):
    cards[i].sort(reverse = True)

for i in range(K):
    curIncDim = getLargestDim();
    print(chr(ord('A') + curIncDim), cards[curIncDim][index[curIncDim]])
    hyperCube[curIncDim] += cards[curIncDim][index[curIncDim]];
    index[curIncDim] += 1;
