import sys
import itertools
import math

primeTable = []

for i in range(2, math.isqrt(1_000_000_000)):
  ifPrime = True
  for e in primeTable:
    if i % e == 0:
      ifPrime = False
      break
  if ifPrime:
    primeTable.append(i)

def ifPrime(N):
  global primeTable
  
  for e in primeTable:
    if N % e == 0:
      return False
    if e > math.isqrt(N):
      return True
  return True

curNumPrimes = []
ans = 0
n = 0

# temp = 100000003

def getAns(newNumber, numToGet):
  global ans
  global n
  global curNumPrimes
  
  if numToGet == len(curNumPrimes) + 1:
    return
  for e in itertools.combinations(curNumPrimes, numToGet):
    multRes = newNumber
    for e2 in e:
      multRes *= e2
    
    if numToGet % 2 == 0:
      ans -= (n - 1) // multRes
    else:
      ans += (n - 1) // multRes
  getAns(newNumber, numToGet + 1)

def testCase():
  global ans, curNumPrimes, n
  
  # n = temp
  # print(temp)
  n = int(sys.stdin.readline())
  if n == 0:
    return False
  
  curNumPrimes = []
  ans = n - 1

  curPIdx = -1
  
  tempN = n
  while tempN != 1:
    if ifPrime(tempN):
      getAns(tempN, 0)
      return True

    curPIdx += 1
    
    if tempN % primeTable[curPIdx] != 0:
      continue
    while tempN % primeTable[curPIdx] == 0:
      tempN //= primeTable[curPIdx]
    getAns(primeTable[curPIdx], 0)
    curNumPrimes.append(primeTable[curPIdx])
  
  return True

while testCase():
  print(ans)
  # temp +=1