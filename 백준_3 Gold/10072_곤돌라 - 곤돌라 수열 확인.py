import sys

n = int(sys.stdin.readline())
arr = list(map(int, sys.stdin.readline().split()))

if len(set(arr)) != n:
  print(0)
  exit(0)

firstLoc = -1
for i in range(n):
  if arr[i] > n: continue
  
  if firstLoc == -1:
    firstLoc = i
  else:
    if arr[firstLoc] + i - firstLoc == n:
      if arr[i] != n:
        print(0)
        exit(0)
    else:
      if (arr[firstLoc] + i - firstLoc) % n != arr[i]:
        print(0)
        exit(0)

print(1)
