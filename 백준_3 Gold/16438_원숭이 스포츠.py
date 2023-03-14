N = int(input())

for i in [1, 2, 4, 8, 16, 32, 64]:
    curLine = ""
    for j in range(N):
        if j % (2 * i) >= i:
            curLine += 'B'
        else:
            curLine += 'A'
    
    if(i >= N):
        curLine = curLine[:-1] + 'B'
    print(curLine)
