N, M, K = map(int, input().split())

revNums = [1 for _ in range(M)]
remains = N - M
i = 0
while remains > 0 and i < len(revNums):
  if remains + revNums[i] <= K:
    revNums[i] += remains
    remains = 0
    break
  remains -= (K - revNums[i])
  revNums[i] = K
  i += 1

if remains > 0 or revNums[0] < K or revNums[-1] > K:
  print(-1)
  exit(0)

ans = []
i = 1
for e in revNums:
  for j in range(i + e - 1, i - 1, -1):
    print(j, end = " ")
  i += e
