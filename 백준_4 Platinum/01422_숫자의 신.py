import sys

K, N = map(int, sys.stdin.readline().split())
nums = [[0, str(int(sys.stdin.readline())), i] for i in range(K)]
for i in range(K):
  nums[i][0] = len(nums[i][1])

nums.sort()

maxLen = nums[-1][0]
lastIdx = nums[-1][2]

for i in range(K):
  
  newNum = nums[i][1]
  while len(newNum) <= maxLen:
    newNum += nums[i][1]
  nums[i].insert(0, newNum)

nums.sort(reverse=True)

ans = ""

for i in range(K):
  if nums[i][3] == lastIdx:    
    for e in range(1 + N - K):
      ans += nums[i][2]
  else:
    ans += nums[i][2]
    

print(ans)