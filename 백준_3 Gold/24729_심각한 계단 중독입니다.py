####231107
##37m 10s

import sys

N = int(input())
numbers = list(map(int, sys.stdin.readline().rstrip().split()))

nums = [0 for _ in range(100002)]
minNum = numbers[0]
for i in numbers:
    nums[i] += 1
    minNum = min(minNum, i)

cnt = 0
curNum = minNum
while True:
    cnt += 1
    nums[curNum] -= 1
    
    if nums[curNum + 1] > 0:    
        if nums[curNum] > 0 or nums[curNum - 1] == 0:
            curNum += 1
        elif nums[curNum - 1] > 0:
            curNum -= 1
        else:
            break
    elif nums[curNum - 1] > 0:
        curNum -= 1
    else:
        break

if cnt == N and abs(curNum - minNum) == 1:
    print(1)
else:
    print(-1)
