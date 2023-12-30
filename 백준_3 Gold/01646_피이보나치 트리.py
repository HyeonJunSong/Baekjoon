N, st, ed = map(int, input().split())

## 피보나치 트리 개수 테이블 만들기
fiboTreeNodeNum = [1, 1]
for i in range(2, N + 1):
  fiboTreeNodeNum.append(fiboTreeNodeNum[i - 2] + fiboTreeNodeNum[i - 1] + 1)


## 최단경로 찾기

# 서로 다른 영역에 올때까지 이동
# 영역 : 0 -> 루트, 1 -> 왼쪽, 2 -> 오른쪽
curStArea = 0
curEdArea = 0
while True:
  if N <= 1:
    exit(0)
  
  if st == 1:
    curStArea = 0
  elif 2 + fiboTreeNodeNum[N - 2] > st:
    curStArea = 1
  else:
    curStArea = 2

  if ed == 1:
    curEdArea = 0
  elif 2 + fiboTreeNodeNum[N - 2] > ed:
    curEdArea = 1
  else:
    curEdArea = 2
  
  if curStArea != curEdArea:
    break
  
  if curStArea == 0:
    exit(0)
  elif curStArea == 1:
    st -= 1
    ed -= 1
    N -= 2
  else:
    st -= 1 + fiboTreeNodeNum[N - 2]
    ed -= 1 + fiboTreeNodeNum[N - 2]
    N -= 1


#왼쪽 경로 구하기
leftPath = ""
curN = N
while st != 1:
  if curN <= 1:
    break
  if st < 2 + fiboTreeNodeNum[curN - 2]:
    leftPath += "U"
    st -= 1
    curN -= 2
  else:
    leftPath += "U"
    st -= 1 + fiboTreeNodeNum[curN - 2]
    curN -= 1


#오른쪽 경로 구하기
rightPath = ""
curN = N
while ed != 1:
  if curN <= 1:
    break
  if ed < 2 + fiboTreeNodeNum[curN - 2]:
    rightPath += "L"
    ed -= 1
    curN -= 2
  else:
    rightPath += "R"
    ed -= 1 + fiboTreeNodeNum[curN - 2]
    curN -= 1

print(leftPath, rightPath, sep="")