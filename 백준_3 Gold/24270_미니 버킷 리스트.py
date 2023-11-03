## 231104
# 10m 12s

N, K = map(int, input().split())
S = list(map(int, input().split()))

ans = 1
for i in range(K - sum(S) + 1, N + K - sum(S) + 1):
  ans *= i
  ans %= 1000000007
print(ans)