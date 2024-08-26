import math
x, y = map(int, input().split())
gcd = math.gcd(x, y)
x //= gcd
y //= gcd
print((x + y - 1) * gcd)