import sys

input()
arr = []
ans = 0
for e in list(map(float, sys.stdin.readlines())):
  if e == 0:
    N = len(arr)
    for i in range(1, N + 1):
      curAns = 1
      for j in range(i):
        curAns *= arr[j]
      
      ans = max(ans, curAns)
      for j in range(i, N):
        curAns /= arr[j - i]
        curAns *= arr[j]
        ans = max(ans, curAns)
    arr = []
  else:
    arr.append(e)

N = len(arr)
for i in range(1, N + 1):
  curAns = 1
  for j in range(i):
    curAns *= arr[j]
  
  ans = max(ans, curAns)
  for j in range(i, N):
    curAns /= arr[j - i]
    curAns *= arr[j]
    ans = max(ans, curAns)

print("%.3f" % ans)