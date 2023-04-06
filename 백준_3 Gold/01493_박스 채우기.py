###전역변수
cubes = []

###입력
inp = input().split(' ')
(length, width, height) = int(inp[0]), int(inp[1]), int(inp[2])

n = int(input())
for i in range(n):
    inp = input().split(' ')
    A, B = int(inp[0]), int(inp[1])
    for j in range(len(cubes) - A):
        cubes.append(0)
    cubes.append(B)

###실행

#이진수로 떼기
i = 0
lengthBinList = []
while length != 1:
    if length % 2 == 1:
        lengthBinList.append(i)
    length //= 2
    i += 1
lengthBinList.append(i)

i = 0
widthBinList = []
while width != 1:
    if width % 2 == 1:
        widthBinList.append(i)
    width //= 2
    i += 1
widthBinList.append(i)

i = 0
heightBinList = []
while height != 1:
    if height % 2 == 1:
        heightBinList.append(i)
    height //= 2
    i += 1
heightBinList.append(i)

#3중 for문 돌며 몇번 큐브가 얼마나 필요한지 체크
cubesNeed = [0 for i in range( min(lengthBinList[-1], widthBinList[-1], heightBinList[-1]) + 1)]
for i in lengthBinList:
    for j in widthBinList:
        for k in heightBinList:
            smallest = min(i, j, k)
            cubesNeed[smallest] += 2 ** ((i - smallest) + (j - smallest) + (k - smallest))

#가지고 있는 큐브로 만들 수 있는지 체크
ans = 0
for i in range(len(cubesNeed) - 1, -1, -1):
    cubesLeft = cubesNeed[i]
    curInd = i
    while curInd >= 0 and cubesLeft != 0:
        if len(cubes) <= curInd:
            curInd -= 1
            cubesLeft *= 8
            continue
        if cubes[curInd] >= cubesLeft:
            cubes[curInd] -= cubesLeft
            ans += cubesLeft
            break
        cubesLeft -= cubes[curInd]
        ans += cubes[curInd]
        cubes[curInd] = 0
        curInd -= 1
        cubesLeft *= 8
    
    if curInd == -1:
        ans = -1
        break

print(ans, end = "")