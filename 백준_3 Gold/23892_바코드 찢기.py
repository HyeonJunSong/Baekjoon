import sys

N, K = map(int, sys.stdin.readline().split())

def getPriceOfBarcode():
  S, P = sys.stdin.readline().split()
  price = 0
  P = int(P)
  
  for i in range(len(S) - 1):
    if S[i] == "(" and S[i + 1] == ")":
      price +=1
  price *= P
  
  if S[-1] == "(" and S[0] == ")":
    price += P - 1

  return price

myMoney = getPriceOfBarcode()
beverageMoney = getPriceOfBarcode()

if myMoney < K:
  print(0)
  exit(0)

if (K - beverageMoney) <= 0:
  print(N)
else:
  ans = min(N, myMoney // (K - beverageMoney))
  moneyLeft = myMoney - ans * (K - beverageMoney)
  
  while moneyLeft - beverageMoney < 0:
    ans -= 1
    moneyLeft += K - beverageMoney
  print(ans)