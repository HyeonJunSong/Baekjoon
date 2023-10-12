####231012
##1h 0m 31s

import sys

# 필수 전역 변수

S = sys.stdin.readline()[:-1]   # 문자열
S = "#".join(S)               # 문자열 전처리

N = len(S)                      # 문자열 길이
r = [0 for i in range(len(S))]  # r[i] : i 번째 단어의 펠린드롬 반지름
far = -1                          # 가장 멀리 온 팰린드롬 끝부분
farMid = -1                       # 가장 멀리 온 팰린드롬 끝부분의 중심점


################################################################ 함수부

## ind의 펠린드롬 반지름 길이 구하는 함수
def getPalinRadius(ind):
  global S, N, r, far, farMid
  
  curR = 0
  # curR 초기화 부분
  if ind <= far:
    curR = min(r[2 * farMid - ind], far - ind)
  
  # 좌우로 넓혀가며 반지름 찾는 부분
  while 0 <= ind - curR - 1 and ind + curR + 1 < N and S[ind - curR - 1] == S[ind + curR + 1]:
    curR += 1
  
  r[ind] = curR
  
  # far 갱신
  if far < ind + curR:
    far = ind + curR
    farMid = ind
  
  return r[ind]

## 인덱스와 계산된 길이를 줬을 때 펠린드롬 길이를 구하는 함수
## getPalinRadius는 전처리된 반지름을 기준으로 하기 때문에 무작정 2 곱하면 안됨
def getPalinLen(ind, r):
  if ind % 2 == 0:  # 실제 단어 일때
    return 1 + (r // 2) * 2
  else: # 더미 단어 일때
    return (r + 1) // 2 * 2
################################################################ 실행부

ans = 0
for i in range(len(S)):
  curAns = getPalinLen(i, getPalinRadius(i))
  if ans < curAns:
    ans = curAns

print(ans)