import sys


def testCase():
  p = sys.stdin.readline().rstrip()
  n = int(sys.stdin.readline())
  x = sys.stdin.readline().rstrip().split(",")
  
  if n == 0:
    x = []
  elif n == 1:
    x[0] = int(x[0][1:-1])
  else:
    x[0] = x[0][1:]
    x[-1] = x[-1][:-1]
    x = list(map(int, x))
  
  ifRev = False
  st = 0
  ed = n - 1
  for e in p:
    if e == 'R':
      ifRev ^= 1
    else:
      if not ifRev:
        st += 1
      else:
        ed -= 1
    
      if st - 1 > ed:
        print("error")
        return
  
  if ifRev:
    ans = reversed(x[st: ed + 1])
    print("[", end = "")
    print(*ans, sep = ",", end = "")
    print("]")
  else:
    ans = x[st : ed + 1]
    print("[", end = "")
    print(*ans, sep = ",", end = "")
    print("]")


for i in range(int(sys.stdin.readline())):
  testCase()