import sys
input = sys.stdin.readline

N, M = map(int, input().split())
trees = list(map(int, input().split()))

st = 0
ed = max(trees) - 1
while st <= ed:
  mid = (st + ed) >> 1

  curCutTree = 0
  for i in range(N):
    if trees[i] <= mid: continue
    curCutTree += trees[i] - mid
  
  if curCutTree >= M:
    st = mid + 1
  else:
    ed = mid - 1

print(ed)