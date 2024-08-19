import itertools

N = int(input())
lights = [input() for _ in range(N)]
individualChanges = 0
for i in range(N):
  for j in range(1, len(lights[i])):
    if lights[i][j - 1] != lights[i][j]:
      individualChanges += 1


ans = float("inf")
for e in itertools.permutations([i for i in range(N)]):  
  curChanges = 0
  for i in range(1, N):
    if lights[e[i - 1]][-1] != lights[e[i]][0]:
      curChanges +=1
  ans = min(ans, curChanges)

print(ans + individualChanges)