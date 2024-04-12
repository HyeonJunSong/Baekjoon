input()
a = []
def b (c):
  global a
  i = 0
  while c > 0:
    if len(a) <= i:
      a.append(0)
    if c % 2 == 1:
      a[i] += 1
    i += 1
    c //= 2
for e in input().split():
  b(int(e))
d = True
for e in a:
  if e % 2 == 1:
    d = False
    break
if d:
  print("cubelover")
else:
  print("koosaga")