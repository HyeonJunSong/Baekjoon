####231118
##1h 49m 5s

import sys
import math

N = int(input())
vals = list(map(int, sys.stdin.readline().split()))

valMap = {}
for e in vals:
    if e in valMap:
        valMap[e] += 1
    else:
        valMap[e] = 1

valMap = sorted([[e, valMap[e]] for e in valMap], reverse=True)

curValMap = {}
ans = []

for e in valMap:
    # 현재 ans 에 gcd가 e[0]인 조합들 구해서 e[1]에서 빼주기
    if e[0] in curValMap:
        e[1] -= curValMap[e[0]]
    
    # 현재 ans에 e[0]의 배수 개수 구하기
    e0Mult = 0
    for e1 in ans:
        if e1[0] % e[0] == 0:
            e0Mult += e1[1]
    
    # 남은 e[1]으로 총 e[0]의 배수 개수 구하기
    e0Nums = (-1 * e0Mult + (e0Mult ** 2 + e[1]) ** 0.5)
    
    if e0Nums > 0:
        if e[0] in curValMap:
            curValMap[e[0]] += e0Nums ** 2
        else:
            curValMap[e[0]] = e0Nums ** 2
        
        for e1 in ans:
            curGcd = math.gcd(e1[0], e[0])
            if curGcd in curValMap:
                curValMap[curGcd] += e0Nums * e1[1] * 2
            else:
                curValMap[curGcd] = e0Nums * e1[1] * 2
                
        ans.append([e[0], int(e0Nums)])

for e in ans:
    for _ in range(e[1]):
        print(e[0], end = " ")