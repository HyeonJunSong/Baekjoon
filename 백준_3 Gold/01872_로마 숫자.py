
N = int(input())

charOfDigit = [
    [100, ['c', 'd', 'm']],
    [10, ['x', 'l', 'c']],
    [1, ['i', 'v', 'x']],
]
orderOfDigit = [
    [9, [0, 2]],
    [8, [1, 0, 0, 0]],
    [7, [1, 0, 0]],
    [6, [1, 0]],
    [5, [1]],
    [4, [0, 1]],
    [3, [0, 0, 0]],
    [2, [0, 0]],
    [1, [0]]
]


def testCase():
    inp = input()
    curStr = ""
    for e in inp:
        if e =="i" or e == "v" or e == "x" or e == "l" or e == "c" or e == "d" or e == "m":
            curStr += e
    ans = 0

    #1000이상
    I = 0
    while I < len(curStr):
        if curStr.find('m', I) == -1: break
        ans += 1000
        I = curStr.find('m', I) + 1
    
    for e1 in charOfDigit:
        for e2 in orderOfDigit:
            ifPossible = True
            tempI = I
            for e3 in e2[1]:
                if curStr.find(e1[1][e3], tempI) == -1:
                    ifPossible = False
                    break
                tempI = curStr.find(e1[1][e3], tempI) + 1
            
            if ifPossible:
                I = tempI
                ans += e1[0] * e2[0]
                break
    
    print(ans)


for _ in range(N):
    testCase()