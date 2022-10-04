num = int(input())
num = 10
tot = 1
for i in range(2, num + 1):
    tot *= i
numStr = str(tot)
cnt = 0
for i in range(numStr.size() - 1, 0, -1):
    if numStr[i] == '0':
        cnt += 1
    else:
        break
print(cnt)