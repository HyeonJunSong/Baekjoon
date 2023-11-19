import sys

N = int(sys.stdin.readline())

def preCal(n):
  return (int(n) - 20) // 2
A = list(map(preCal, sys.stdin.readline().split()))

A.append(0)
N += 1

def getCurElement(W):
  res = [W, W // 20]
  
  if W % 20 > 0:
    res[1] += 1
  
  return res


stack = []
totWeight = 0
totNum = 0

stack.append(getCurElement(A[0]))
totWeight += stack[-1][0]
totNum += stack[-1][1]

for i in range(1, N):
  if A[i] - A[i - 1] > 0:
    stack.append(getCurElement(A[i] - A[i - 1]))
    totWeight += stack[-1][0]
    totNum += stack[-1][1]
  else:
    curWeight = A[i - 1] - A[i]
    while len(stack) > 0 and curWeight >= stack[-1][0]:
      popped = stack.pop()
      totWeight += popped[0]
      totNum += popped[1]
      curWeight -= popped[0]
    if curWeight == 0:
      continue
    
    curWeightBabel = getCurElement(curWeight)
    totWeight += curWeightBabel[0]
    totNum += curWeightBabel[1]
    
    alter = getCurElement(stack[-1][0] - curWeight)
    totNum += alter[1] + curWeightBabel[1] - stack[-1][1]
    stack[-1] = alter

print(totWeight * 2, totNum * 2)