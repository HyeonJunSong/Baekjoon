password = input()
k = int(input()) - 1

changeNums = 0
for e in password:
    if e == '1' or e == '2' or e == '6' or e == '7':
        changeNums += 1

if len(bin(k)) - 2 > changeNums:
    print(-1)
    exit(0)

binK = bin(k)[2:]
binKIdx = -1
ans = ""
for e in reversed(password):
    if e == '1' or e == '2' or e == '6' or e == '7':
        if -1 * binKIdx <= len(binK) and binK[binKIdx] == '1':
            if e == '1' or e == '6':
                ans += '6'
            else:
                ans += '7'
        else:
            if e == '1' or e == '6':
                ans += '1'
            else:
                ans += '2'
        binKIdx -= 1
    else:
        ans += e
print(*reversed(ans), sep = "")