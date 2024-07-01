import sys

def testCase():
  
  n = int(sys.stdin.readline())
  s, t = map(int, sys.stdin.readline().split())

  ans = 0

  while n > 0 :
    if n % 2 == 0:
      ans += min((n // 2) * s, t)
      n //= 2
    else:
      ans += s
      n -= 1

  print(ans)


T = int(sys.stdin.readline())

for t in range(T):
  testCase()
