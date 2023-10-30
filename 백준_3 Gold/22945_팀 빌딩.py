import sys

sys.setrecursionlimit(300000)

N = int(sys.stdin.readline())
x = list(map(int, sys.stdin.readline().split()))

arr = sorted([[x[i], i] for i in range(N)], reverse=True)

ans = 0
left = arr[0][1]
right = arr[0][1]
for i in range(1, N):
  left = min(left, arr[i][1])
  right = max(right, arr[i][1])
  
  cur = max(arr[i][1] - left - 1, right - arr[i][1] - 1)
  if ans < cur * arr[i][0]:
    ans = cur * arr[i][0]

print(ans)