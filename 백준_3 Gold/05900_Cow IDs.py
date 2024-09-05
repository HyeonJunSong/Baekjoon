
N, K = map(int, input().split())

def combination(n, k):
  ans = 1
  for i in range(k):
    ans *= n - i
  for i in range(1, k + 1):
    ans //= i
  return  ans

n, k, length = N, K, -1
while True:
  if k == 0:
    for _ in range(length):
      print('0', end = "")
    break
  if n == 1:
    if length != -1:
      for _ in range(length - k):
        print('0', end = "")
    print('1' * k, end = "")
    break

  for i in range(k, 10000001):
    if n - combination(i - 1, k - 1) > 0:
      n -= combination(i - 1, k - 1)
      continue

    if length != -1:
      for _ in range(length - i):
        print('0', end = "")
    print('1', end = "")
    n, k, length = n, k - 1, i - 1
    break
