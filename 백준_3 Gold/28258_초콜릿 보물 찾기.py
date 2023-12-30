import sys

checks = [
  [3, 2, 0],
  [5, 4, 0],
  [7, 6, 0],
  [9, 8, 0],
  [9, 9, 1],
  [7, 9, 3],
  [5, 9, 5],
  [3, 9, 7],
]
dir = [
  [-1,  0],
  [ 0,  1],
  [ 1,  0],
  [ 0, -1],
]

def ask(r, c):
  print("?", r, c)
  sys.stdout.flush()
  return input()

def answer(r1, c1, r2, c2):
  print("!", r1, c1, r2, c2)
  sys.stdout.flush()
  exit(0)

for e in checks:
  for i in range(e[0]):
    res = ask(e[1] - i, e[2] + i)
    
    if res == '0':
      continue
    
    for d in range(3):
      if 0 <= e[1] - i + dir[d][0] <= 9 and 0 <= e[2] + i + dir[d][1] <= 9:
        res2 = ask(e[1] - i + dir[d][0], e[2] + i + dir[d][1])
        
        if res2 == "0":
          continue
        
        answer(e[1] - i, e[2] + i, e[1] - i + dir[d][0], e[2] + i + dir[d][1])
        
    answer(e[1] - i, e[2] + i, e[1] - i + dir[3][0], e[2] + i + dir[3][1])

res = ask(0, 0)
if res == "1":
  res2 = ask(0, 1)
  if res2 == "1":
    answer(0, 0, 0, 1)
  else:
    answer(0, 0, 1, 0)
else:
  res2 = ask(9, 8)
  if res2 == "1":
    answer(9, 9, 9, 8)
  else:
    answer(9, 9, 8, 9)
  