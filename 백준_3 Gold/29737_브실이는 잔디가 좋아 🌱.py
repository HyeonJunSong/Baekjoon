import sys

N, W = map(int, sys.stdin.readline().rstrip().split())

ranks = []

def calStreak():
    id = sys.stdin.readline().rstrip()
    record = []
    for i in range(7):
        record.append(sys.stdin.readline().rstrip())
    
    curWeek = 0
    curDay = 0
    
    minStreak = [0, float("INF"), [float("INF"), float("INF")]]
    curStreak = [0, 0, [0, 0]]
    streakFails = 0
    curFreeze = 0
    while True:
        if record[curDay][curWeek] == 'O':
            if curStreak[0] != 0:
                curStreak[1] += curFreeze
            curFreeze = 0
            curStreak[0] -= 1
        elif record[curDay][curWeek] == 'X':
            streakFails += 1
            if minStreak > curStreak:
                minStreak = curStreak

            if curDay == 6:
                curStreak = [0, 0, [curWeek + 1, 0]]
            else:
                curStreak = [0, 0, [curWeek, curDay + 1]]
        elif record[curDay][curWeek] == 'F':
            curFreeze += 1
        
        if curDay == 6:
            curDay = 0
            if curWeek == W - 1:
                break
            else:
                curWeek += 1
        else:
            curDay += 1

    if minStreak > curStreak:
        minStreak = curStreak
    ranks.append(minStreak + [streakFails, id])

for i in range(N):
    calStreak()

ranks.sort()
# print(ranks)

curRank = 1
print("%d. %s" % (1, ranks[0][4]))
for i in range(1, len(ranks)):
    if ranks[i - 1][:4] != ranks[i][:4]:
        curRank += 1
    print("%d. %s" % (curRank, ranks[i][4]))