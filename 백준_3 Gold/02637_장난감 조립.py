#함수
def getBasicParts(product : int):
    global partsNeed, cache
    
    basicParts = {}
    for i in partsNeed[product]:
        if len(partsNeed[i[0]]) == 0:
            if i[0] in basicParts:
                basicParts[i[0]] += i[1]
            else:
                basicParts[i[0]] = i[1]            
        
        if len(cache[i[0]]) == 0:
            cache[i[0]] = getBasicParts(i[0])
        curBasicParts = cache[i[0]]
        for part in curBasicParts:
            if part in basicParts:
                basicParts[part] += curBasicParts[part] * i[1]
            else:
                basicParts[part] = curBasicParts[part] * i[1]
    
    return basicParts

#입력
N = int(input())
partsNeed = [[] for i in range(N + 1)]
cache = [{} for i in range(N + 1)]

M = int(input())
for i in range(M):
    X, Y, K = map(int, input().split())
    partsNeed[X].append([Y, K])
#실행


for i in sorted(getBasicParts(N).items()):
    print(i[0], i[1])