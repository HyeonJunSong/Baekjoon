import sys
input = sys.stdin.readline

N, K, Q = map(int, input().split())

messages = [list(input().split()) for _ in range(K)]

if messages[Q - 1][0] == '0':
  print(-1)
  exit(0)

st = Q - 1
while st >= 0 and messages[st][0] == messages[Q - 1][0]:
  st -= 1

read = [False for _ in range(N)]
read[0] = True
for i in range(st + 1, K):
  read[ord(messages[i][1]) - ord('A')] = True


for i in range(N):
  if read[i]: continue
  print(chr(ord('A') + i), end = " ")