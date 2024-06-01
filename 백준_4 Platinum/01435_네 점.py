inp = [list(map(int, input().split())) for _ in range(4)]

a2 = inp[0][1]
a3 = (a2**2 + inp[0][2]**2 - inp[1][2]**2) / (2*a2)
if inp[0][2]**2 - a3**2 < 0:
  print("NO")
  exit(0)
b3 = (inp[0][2]**2 - a3**2) ** 0.5

r1 = inp[0][3]
r2 = inp[1][3]
r3 = inp[2][3]

x = (a2**2 + r1**2 - r2**2) / (2*a2)

if r1**2 - x**2 < 0:
  print("NO")
  exit(0)

r = (r1**2 - x**2) ** 0.5

if (x - a3)**2 + (r-b3)**2 <= r3**2 <= (x - a3)**2 + (r+b3)**2:
  print("YES")
else:
  print("NO")
