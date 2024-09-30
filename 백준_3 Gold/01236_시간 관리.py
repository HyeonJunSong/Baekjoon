N = int(input())
tasks = [list(map(int, input().split())) for _ in range(N)]
tasks.sort(key= lambda a: -a[1])

curTime = float("inf")
for e in tasks:
  curTime = min(curTime - e[0], e[1] - e[0])

if curTime < 0:
  print(-1)
else:
  print(curTime)