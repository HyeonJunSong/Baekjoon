X0, N = map(int, input().split())
X0 = str(bin(X0))[2:]

if sum(list(map(int, X0))) < N:
  print(-1)
  exit(0)

ans = []
for i in range(len(X0)):
  if X0[i] == '0': continue
  if N == 1:
    ans.append(0)
    break
  ans.append(int(X0[i + 1:], 2))
  N -= 1

print(*ans)