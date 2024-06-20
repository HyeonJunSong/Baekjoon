import sys

k = 0
origin = ""
comp = ""
wordDict = {}

def ifPossible(oIdx, cIdx):
  global wordDict
  
  if oIdx == len(origin) and cIdx == len(comp): return True
  if oIdx == len(origin) or cIdx == len(comp): return False
  
  if origin[oIdx] in wordDict:
    if len(comp) - cIdx < len(wordDict[origin[oIdx]]): return False
    if comp[cIdx: cIdx + len(wordDict[origin[oIdx]])] == wordDict[origin[oIdx]]:
      return ifPossible(oIdx + 1, cIdx + len(wordDict[origin[oIdx]]))
  else:
    for i in range(1, min(k, len(comp) - cIdx) + 1):
      wordDict[origin[oIdx]] = comp[cIdx: cIdx + i]
      if ifPossible(oIdx + 1, cIdx + i): return True
      del wordDict[origin[oIdx]]
  return False

def testCase():
  global k, origin, comp, wordDict
  wordDict = {}
  k = int(sys.stdin.readline())
  origin = sys.stdin.readline()
  if origin[-1] == "\n": origin = origin[:-1]
  comp = sys.stdin.readline()
  if comp[-1] == "\n": comp = comp[:-1]
  
  if ifPossible(0, 0): print(1)
  else: print(0)

T = int(sys.stdin.readline())
for t in range(T):
  testCase()