
#입력
N = int(input())
nums = []
totLen = 0
for i in range(N):
    nums.append(int(input()))
    totLen += len(str(nums[-1]))
K = int(input())

remainderSetDic = {}
def getPossibleSet(numList):
    retRemainderSet = {}
    
    ifAllFalse = True
    for i in range(N):
        if not numList[i]:
            continue
        ifAllFalse = False
        
        numList[i] = False
        numStr = ""
        lenStr = 0
        for j in range(N):
            if numList[j]:
                numStr += '1'
                lenStr += len(str(nums[j]))
            else:
                numStr += '0'
        
        if numStr not in remainderSetDic:
            remainderSetDic[numStr] = getPossibleSet(numList)
        
        curRemainder = (nums[i] % K) * (10 ** lenStr) % K
        
        for j in remainderSetDic[numStr]:
            temp = (j + curRemainder) % K
            if temp in retRemainderSet:
                retRemainderSet[temp] += remainderSetDic[numStr][j]
            else:
                retRemainderSet[temp] = remainderSetDic[numStr][j]
        
        numList[i] = True
    if ifAllFalse:
        retRemainderSet[0] = 1
    return retRemainderSet

totPossibleSet = getPossibleSet([True for i in range(N)])

totNum = 1
for i in range(2, N + 1):
    totNum *= i

if 0 not in totPossibleSet:
    print("0/1", end = "")
else:
    possibleNum = totPossibleSet[0]
    
    large = totNum
    small = possibleNum
    while True:
        if large % small == 0:
            break
        temp = large
        large = small
        small = temp % small
    
    print(possibleNum//small, '/', totNum//small, sep = "", end = "")