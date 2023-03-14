N = int(input())
villages = []

for i in range(N):
    inp = input().split(' ')
    villages.append([int(inp[0]), int(inp[1])])

ifEveryThing0 = True
for i in villages:
    if i[1] != 0:
        ifEveryThing0 = False
        break

if ifEveryThing0:
    print(-1000000000)
else:
    villages.sort()
    sum_front = [villages[i][1] for i in range(N)]
    sum_back = [villages[i][1] for i in range(N)]

    for i in range(1, N):
        sum_front[i] += sum_front[i - 1]
        sum_back[N - i - 1] += sum_back[N - i]

    ans = 0
    ansInd = 0
    prevResult = 0

    for i in range(1, N):
        prevResult += sum_front[i - 1] * (villages[i][0] - villages[i-1][0])
        prevResult -= sum_back[i] * (villages[i][0] - villages[i-1][0])

        if prevResult < ans:
            ans = prevResult
            ansInd = i
    print(villages[ansInd][0])
