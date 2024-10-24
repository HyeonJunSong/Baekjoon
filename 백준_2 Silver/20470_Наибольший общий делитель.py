import math

n, d = map(int, input().split())
nums = list(map(int, input().split()))
newNums = []
for e in nums:
  if e >= d and e % d == 0:
    newNums.append(e // d)

if len(newNums) == 0 or math.gcd(*newNums) != 1:
  print(-1)
else:
  print(len(newNums))
  print(*list(map(lambda x: x * d, newNums)))