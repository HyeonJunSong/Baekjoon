
N = int(input())
nums = input().split()
ops = list(map(int, input().split()))

maxAns = float("-inf")
minAns = float("inf")
def getAns(idx, curOp, curCal):
  
  if idx == N:
    global maxAns, minAns
    maxAns = max(maxAns, eval(curCal))
    minAns = min(minAns, eval(curCal))
    return
  
  if curOp[0] > 0:
    curOp[0] -= 1
    getAns(idx + 1, curOp, curCal + '+' + nums[idx])
    curOp[0] += 1
    
  if curOp[1] > 0:
    curOp[1] -= 1
    getAns(idx + 1, curOp, curCal + '-' + nums[idx])
    curOp[1] += 1
    
  if curOp[2] > 0:
    curOp[2] -= 1
    getAns(idx + 1, curOp, curCal + '*' + nums[idx])
    curOp[2] += 1
    
  if curOp[3] > 0:
    curOp[3] -= 1
    getAns(idx + 1, curOp, curCal + '//' + nums[idx])
    curOp[3] += 1

getAns(1, ops, nums[0])
print(maxAns, minAns, sep = "\n", end = "")