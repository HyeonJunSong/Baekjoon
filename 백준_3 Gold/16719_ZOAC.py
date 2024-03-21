
string = input()

def getAnsList(S):
  
  if len(S) == 1:
    return [S]
  
  midIdx = -1
  for i in range(len(S)):
    if midIdx == -1 or S[midIdx] > S[i]:
      midIdx = i
  
  if midIdx == len(S) - 1:
    return [S[midIdx]] + list(map(lambda s: s + S[midIdx], getAnsList(S[:midIdx])))
  if midIdx == 0:
    return [S[midIdx]] + list(map(lambda s: S[midIdx] + s,  getAnsList(S[midIdx + 1:])))
  
  return [S[midIdx]] + list(map(lambda s: S[midIdx] + s,  getAnsList(S[midIdx + 1:]))) + list(map(lambda s: s + S[midIdx:], getAnsList(S[:midIdx])))

print(*getAnsList(string), sep = "\n")