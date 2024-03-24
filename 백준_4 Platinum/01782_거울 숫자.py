
A, B = map(int, input().split())

def getNumOfMirrors(num):
  num = list(map(int, list(str(num))))

  ans = 0
  for i in range(1, len(num)):
    if i == 1:
      ans += 3
    else:
      if i % 2 == 0:
        ans += 4 * (5 ** (i // 2 - 1)) 
      else:
        ans += 4 * (5 ** (i // 2 - 1)) * 3
  
  ifLastAvailable = True
  for i in range(len(num) // 2):
    curAns = 0
    
    if i > 0:
      if num[i] > 8:
        curAns = 5
      elif num[i] > 5:
        curAns = 4
      elif num[i] > 2:
        curAns = 3
      elif num[i] > 1:
        curAns = 2
      elif num[i] > 0:
        curAns = 1
    else:
      if num[i] > 8:
        curAns = 4
      elif num[i] > 5:
        curAns = 3
      elif num[i] > 2:
        curAns = 2
      elif num[i] > 1:
        curAns = 1
    
    if len(num) % 2 == 0:
      ans += curAns * (5 ** (len(num) // 2 - i - 1))
    else:
      ans += curAns * (5 ** (len(num) // 2 - i - 1)) * 3
    
    if num[i] != 0 and num[i] != 1 and num[i] != 2 and num[i] != 5 and num[i] != 8:
      ifLastAvailable = False
      break
  
  if ifLastAvailable:
    if len(num) % 2 == 1:
      if num[len(num) // 2] > 8:
        ans += 3
      elif num[len(num) // 2] > 1:
        ans += 2
      elif num[len(num) // 2] > 0:
        ans += 1
    
      if num[len(num) // 2] != 0 and num[len(num) // 2] != 1 and num[len(num) // 2] != 8:
        ifLastAvailable = False
    
    for i in range(len(num) // 2 - 1, -1, -1):
      if num[i] == 0:
        if num[len(num) - i - 1] == 0:
          continue
        elif num[len(num) - i - 1] > 0:
          break
        else:
          ifLastAvailable = False
          break
      elif num[i] == 1:
        if num[len(num) - i - 1] == 1:
          continue
        elif num[len(num) - i - 1] > 1:
          break
        else:
          ifLastAvailable = False
          break
      elif num[i] == 2:
        if num[len(num) - i - 1] == 5:
          continue
        elif num[len(num) - i - 1] > 5:
          break
        else:
          ifLastAvailable = False
          break
      elif num[i] == 5:
        if num[len(num) - i - 1] == 2:
          continue
        elif num[len(num) - i - 1] > 2:
          break
        else:
          ifLastAvailable = False
          break
      elif num[i] == 8:
        if num[len(num) - i - 1] == 8:
          continue
        elif num[len(num) - i - 1] > 8:
          break
        else:
          ifLastAvailable = False
          break
  
  if ifLastAvailable:
    ans += 1
  
  return ans

if A == 0:
  print(getNumOfMirrors(B))
else:
  print(getNumOfMirrors(B) - getNumOfMirrors(A - 1))