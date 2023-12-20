####231220
##32m 03s

import sys
import math

GCD , LCM = map(int, sys.stdin.readline().split())
mul = LCM // GCD

ansSum = float("inf")
ansI = 0

for i in range(1, int(math.sqrt(mul)) + 1):
  if mul % i != 0:
    continue
  if math.gcd(i, mul // i) != 1:
    continue
  
  if ansSum > i + mul // i:
    ansSum = i + mul // i
    ansI = i

print(ansI * GCD, GCD * (mul // ansI))