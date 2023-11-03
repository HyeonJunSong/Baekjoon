####231030
##54m 11s

import sys

sys.setrecursionlimit(10000)

money = []
k = 0
while 10 ** k <= 10 ** 15:
  money.append(10 ** k)
  k += 1

k = 0
while 25 * (100 ** k) <= 10 ** 15:
  money.append(25 * (100 ** k))
  k += 1

money.sort(reverse=True)

ans = 987654321
def getMinMoney(i, price, curCnt):
  global ans
  if ans <= curCnt:
    return
  
  if i == len(money) - 1:
    if ans > curCnt + price:
      ans = curCnt + price
    return
  
  if price < money[i]:
    getMinMoney(i + 1, price, curCnt)
    return
  
  if i % 3 == 2:
    getMinMoney(i, price - money[i], curCnt + 1)
    getMinMoney(i + 1, price, curCnt)
  else:
    getMinMoney(i + 1, price % money[i], curCnt + price // money[i])
  


T = int(sys.stdin.readline())
for _ in range(T):
  price = int(sys.stdin.readline())
  
  ans = 987654321
  
  getMinMoney(0, price, 0)
  print(ans)