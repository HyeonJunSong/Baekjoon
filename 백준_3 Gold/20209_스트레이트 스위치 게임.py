import itertools

N, K = map(int, input().split())
cubeNums = list(map(int, input().split()))
switches = [list(map(int, input().split()))[1:] for _ in range(K)]

ans = float("inf")

for e in itertools.product([_ for _ in range(5)], repeat=K):
  curCubeNums = cubeNums.copy()
  for i in range(K):
    for j in range(len(switches[i])):
      curCubeNums[switches[i][j] - 1] += (i + 1) * e[i]
    
  ifAns = True
  for i in range(1, N):
    if (curCubeNums[0] % 5) == (curCubeNums[i] % 5): continue
    ifAns = False
    break
  if ifAns:
    ans = min(ans, sum(e))

if ans == float("inf"):
  print(-1)
else:
  print(ans)