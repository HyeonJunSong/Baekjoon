import sys
sys.setrecursionlimit(300000)

route = input()

divisor = 1_000_000_000

memo1 = [[-1 for j in range(len(route))] for i in range(len(route))]
memo2 = [[[-1 for k in range(26)] for j in range(len(route))] for i in range(len(route))]
def getNumOfTrees_child(st, ed):
  if route[st] != route[ed]:
    return 0
  
  if ed - st + 1 == 2:
    return 0
  elif ed - st + 1 == 1:
    return 1
  
  if memo2[st + 1][ed - 1][ord(route[st]) - ord('A')] == -1:
    memo2[st + 1][ed - 1][ord(route[st]) - ord('A')] = getNumOfTrees_children(st + 1, ed - 1, ord(route[st]) - ord('A'))
  return memo2[st + 1][ed - 1][ord(route[st]) - ord('A')]

def getNumOfTrees_children(st, ed, seperator):
  if st == ed:
    return 1
  
  numOfTrees = 0
  for i in range(st, ed - 1):
    if route[i + 1] != chr(seperator + ord('A')):
      continue
    if memo1[st][i] == -1:
      memo1[st][i] = getNumOfTrees_child(st, i)
    
    if memo2[i + 2][ed][seperator] == -1:
      memo2[i + 2][ed][seperator] = getNumOfTrees_children(i + 2, ed, seperator)
      
    numOfTrees += (memo1[st][i] * memo2[i + 2][ed][seperator]) % divisor
  
  if memo1[st][ed] == -1:
    memo1[st][ed] = getNumOfTrees_child(st, ed)
  numOfTrees += memo1[st][ed]
  return numOfTrees % divisor

print(getNumOfTrees_child(0, len(route) - 1))