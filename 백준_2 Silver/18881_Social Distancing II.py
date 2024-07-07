import sys

N = int(sys.stdin.readline())
cows = sorted(list(map(lambda x: list(map(int, x.split())) , sys.stdin.readlines())))

minDis = float("inf")
for i in range(N):
    if cows[i][1] == 1: continue

    if i > 0 and cows[i - 1][1] == 1:
        minDis = min(minDis, cows[i][0] - cows[i - 1][0])
    if i < N - 1 and cows[i + 1][1] == 1:
        minDis = min(minDis, cows[i + 1][0] - cows[i][0])

ans = 0
for i in range(N):
    if cows[i][1] == 0: continue

    if i == 0 or cows[i][0] - cows[i - 1][0] >= minDis:
        ans += 1
print(ans)