#2202.09.06
#1h 47m
#한시간 삽질한 결과
#완전탐색으로 푸니까 풀려버렸따

N = int(input())
M = int(input())
if M != 0:
    broken = input().split(' ')
else:
    broken = []
ans = abs(100 - N)

if M != 10:
    #위로 가장 가까운거
    if M != 9 or '0' in broken:
        upper = N
        while True:
            curLis = list(str(upper))
            ifPossible = True
            for i in curLis:
                if i in broken:
                    ifPossible = False
                    break
            if ifPossible:
                if ans > upper - N + len(str(upper)):
                    ans = upper - N + len(str(upper))
                break;
            upper += 1
        

    #밑으로 가장 가까운거
    lower = N
    while True:
        curLis = list(str(lower))
        ifPossible = True
        for i in curLis:
            if i in broken:
                ifPossible = False
                break
        if ifPossible:
            if int(lower) < 0:
                break
            
            if ans > N - lower + len(str(lower)):
                ans = N - lower + len(str(lower))
            break
        lower -= 1


print(ans)
