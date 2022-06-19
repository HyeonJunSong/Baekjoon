
n = int(input())

for i in range(n):
    inp = input().split(' ')
    t = int(inp[0])

    dic = {}
    tot = 0
    for j in range(t):
        tot += 1
        if inp[j + 1] in dic:
            dic[inp[j + 1]] += 1
        else:
            dic[inp[j + 1]] = 1

    Max = 0
    MaxArm = ''
    for j in dic:
        if dic[j] > Max:
            Max = dic[j]
            MaxArm = j

    if(tot / 2 < Max):
        print(MaxArm)
    else:
        print("SYJKGW")