A, B = map(int, input().split())

def sigFx(x):
  if x == 0: return 0
  if x == 1: return 1

  n = 0
  val = 1
  while val <= x:
    val *= 2
    n += 1
  n -= 1

  return 2 ** (n - 1) * n + sigFx(x - 2 ** n) + x - 2 ** n + 1

print(sigFx(B) - sigFx(A - 1))
