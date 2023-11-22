import sys
sys.setrecursionlimit(300000)

N = int(input())
arr = list(map(int, sys.stdin.readline().split()))

def findIndToInsert(arr, target, func):
  st = 0
  ed = len(arr) - 1
  
  while st <= ed:
    mid = (st + ed) // 2
    if func(arr[mid], target):
      st = mid + 1
    else:
      ed = mid - 1
  
  return ed

def increase(a, b):
  return a < b

increaseArr = [arr[0]]

for i in range(1, len(arr)):
  incInd = findIndToInsert(increaseArr, arr[i], increase)
  if incInd == len(increaseArr) - 1:
    increaseArr.append(arr[i])
  else:
    increaseArr[incInd + 1] = arr[i]

print(N - len(increaseArr))