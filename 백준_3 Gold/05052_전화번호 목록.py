import sys

t = int(sys.stdin.readline())

def testCase():
  n = int(sys.stdin.readline())
  telNums = []
  for i in range(n):
    telNums.append(sys.stdin.readline()[:-1])
  telNums.sort(key= lambda x : len(x))
  
  telMap = {-1: False}
  for i in telNums:
    curTelMap = telMap
    for j in i:
      if curTelMap[-1]:
        return False
      
      if j in curTelMap:
        curTelMap = curTelMap[j]
      else:
        curTelMap[j] = {-1: False}
        curTelMap = curTelMap[j]
    curTelMap[-1] = True
  
  print(telMap)
  return True

for i in range(t):
  if testCase():
    print("YES")
  else:
    print("NO")