
notTable = [2, 1, 0]

mulTable = [
  [0, 0, 0],
  [0, 1, 1],
  [0, 1, 2],
]

addTable = [
  [0, 1, 2],
  [1, 1, 2],
  [2, 2, 2],
]

class Op:
  def __init__(self, num):
    self.num = num
  def __neg__(self):
    return Op(notTable[self.num])
  def __add__(self, op):
    return Op(addTable[self.num][op.num])
  def __mul__(self, op):
    return Op(mulTable[self.num][op.num])

while True:
  inp = input()
  if inp == '.': break

  inp = inp.replace('0', "Op(0)")
  inp = inp.replace('1', "Op(1)")
  inp = inp.replace('2', "Op(2)")

  ans = 0

  for p in range(3):
    for q in range(3):
      for r in range(3):
        P = Op(p)
        Q = Op(q)
        R = Op(r)

        if eval(inp).num == 2:
          ans += 1
  
  print(ans)
