import sys

#line에 대해 point가 CCW에 있는지 판단.
#1이면 CCW, -1이이면 CW, 0이면 가운데 선
def CCWSide(line, point):
  a = line[1][0] - line[0][0]
  b = line[1][1] - line[0][1]
  c = point[0] - line[0][0]
  d = point[1] - line[0][1]
  
  res = a * d - c * b
  if res > 0: return 1
  elif res < 0: return -1
  else: return 0

def ifCross(line1, line2):
  
  ABC = CCWSide(line1, line2[0])
  ABD = CCWSide(line1, line2[1])
  
  CDA = CCWSide(line2, line1[0])
  CDB = CCWSide(line2, line1[1])
  
  if ABC == 0 or ABD == 0 or CDA == 0 or CDB == 0:
    if ABC == 0 and ABD == 0 and CDA == 0 and CDB == 0:
      if line1[0][0] == line1[1][0]:
        if max(line1[0][1], line1[1][1]) < min(line2[0][1], line2[1][1]) \
        or max(line2[0][1], line2[1][1]) < min(line1[0][1], line1[1][1]): return 0
        elif max(line1[0][1], line1[1][1]) == min(line2[0][1], line2[1][1]) \
        or max(line2[0][1], line2[1][1]) == min(line1[0][1], line1[1][1]): return 1
        else: return 3
      else:
        if max(line1[0][0], line1[1][0]) < min(line2[0][0], line2[1][0]) \
        or max(line2[0][0], line2[1][0]) < min(line1[0][0], line1[1][0]): return 0
        elif max(line1[0][0], line1[1][0]) == min(line2[0][0], line2[1][0]) \
        or max(line2[0][0], line2[1][0]) == min(line1[0][0], line1[1][0]): return 1
        else: return 3
    
    if ABC == 0 or ABD == 0:
      if CDA * CDB <= 0: return 1
      else: return 0
    elif CDA == 0 or CDB == 0:
      if ABC * ABD <= 0: return 1
      else: return 0
    
  else:
    if ABC * ABD < 0 and CDA * CDB < 0: return 2
    else: return 0

N = int(sys.stdin.readline())
lines = list(map(lambda x: [list(map(int, x.split()))[:2], list(map(int, x.split()))[2:]], sys.stdin.readlines()))

ans = [[3 for j in range(N)] for i in range(N)]
for i in range(N - 1):
  for j in range(i + 1, N):
    res = ifCross(lines[i], lines[j])
    ans[i][j] = res
    ans[j][i] = res

for e in ans:
  print(*e, sep = "")