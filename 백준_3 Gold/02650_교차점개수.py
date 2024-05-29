import sys

def ifCross(line1, line2):
  if line1[0] == line1[2]:
    return (line2[0] == line1[0] and (min(line1[1], line1[3]) < line2[1] < max(line1[1], line1[3]))) \
          ^ (line2[2] == line1[0] and (min(line1[1], line1[3]) < line2[3] < max(line1[1], line1[3])))
  
  if line1[0] == 1:
    if line1[2] == 2:
      return (line2[0] == 3 or (line2[0] == 1 and line2[1] < line1[1]) or (line2[0] == 2 and line2[1] < line1[3])) \
           ^ (line2[2] == 3 or (line2[2] == 1 and line2[3] < line1[1]) or (line2[2] == 2 and line2[3] < line1[3]))
    if line1[2] == 3:
      return ((line2[0] == 1 and line2[1] < line1[1]) or (line2[0] == 3 and line2[1] < line1[3])) \
           ^ ((line2[2] == 1 and line2[3] < line1[1]) or (line2[2] == 3 and line2[3] < line1[3]))
    if line1[2] == 4:
      return (line2[0] == 2 or line2[0] == 3 or (line2[0] == 1 and line2[1] < line1[1]) or (line2[0] == 4 and line2[1] > line1[3])) \
           ^ (line2[2] == 2 or line2[2] == 3 or (line2[2] == 1 and line2[3] < line1[1]) or (line2[2] == 4 and line2[3] > line1[3]))
           
  if line1[0] == 2:
    if line1[2] == 1:
      return (line2[0] == 3 or (line2[0] == 1 and line2[1] < line1[3]) or (line2[0] == 2 and line2[1] < line1[1])) \
           ^ (line2[2] == 3 or (line2[2] == 1 and line2[3] < line1[3]) or (line2[2] == 2 and line2[3] < line1[1]))
    if line1[2] == 3:
      return ((line2[0] == 2 and line2[1] < line1[1]) or (line2[0] == 3 and line2[1] > line1[3])) \
           ^ ((line2[2] == 2 and line2[3] < line1[1]) or (line2[2] == 3 and line2[3] > line1[3]))
    if line1[2] == 4:
      return (line2[0] == 1 or line2[0] == 3 or (line2[0] == 2 and line2[1] < line1[1]) or (line2[0] == 4 and line2[1] < line1[3])) \
           ^ (line2[2] == 1 or line2[2] == 3 or (line2[2] == 2 and line2[3] < line1[1]) or (line2[2] == 4 and line2[3] < line1[3]))
    
  if line1[0] == 3:
    if line1[2] == 1:
      return ((line2[0] == 3 and line2[1] < line1[1]) or (line2[0] == 1 and line2[1] < line1[3])) \
           ^ ((line2[2] == 3 and line2[3] < line1[1]) or (line2[2] == 1 and line2[3] < line1[3]))
    if line1[2] == 2:
      return ((line2[0] == 3 and line2[1] > line1[1]) or (line2[0] == 2 and line2[1] < line1[3])) \
           ^ ((line2[2] == 3 and line2[3] > line1[1]) or (line2[2] == 2 and line2[3] < line1[3]))
    if line1[2] == 4:
      return (line2[0] == 1 or (line2[0] == 3 and line2[1] < line1[1]) or (line2[0] == 4 and line2[1] < line1[3])) \
           ^ (line2[2] == 1 or (line2[2] == 3 and line2[3] < line1[1]) or (line2[2] == 4 and line2[3] < line1[3]))

  if line1[0] == 4:
    if line1[2] == 1:
      return (line2[0] == 2 or line2[0] == 3 or (line2[0] == 4 and line2[1] > line1[1]) or (line2[0] == 1 and line2[1] < line1[3])) \
           ^ (line2[2] == 2 or line2[2] == 3 or (line2[2] == 4 and line2[3] > line1[1]) or (line2[2] == 1 and line2[3] < line1[3]))
    if line1[2] == 2:
      return (line2[0] == 1 or line2[0] == 3 or (line2[0] == 4 and line2[1] < line1[1]) or (line2[0] == 2 and line2[1] < line1[3])) \
           ^ (line2[2] == 1 or line2[2] == 3 or (line2[2] == 4 and line2[3] < line1[1]) or (line2[2] == 2 and line2[3] < line1[3]))
    if line1[2] == 3:
      return (line2[0] == 1 or (line2[0] == 4 and line2[1] < line1[1]) or (line2[0] == 3 and line2[1] < line1[3])) \
           ^ (line2[2] == 1 or (line2[2] == 4 and line2[3] < line1[1]) or (line2[2] == 3 and line2[3] < line1[3]))
    
      
N = int(sys.stdin.readline())
N //= 2
points = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]

ans = 0
crosses = [0 for i in range(N)]
for i in range(N - 1):
  for j in range(i + 1, N):
    if ifCross(points[i], points[j]):
      ans += 1
      crosses[i] += 1
      crosses[j] += 1

print(ans)
print(max(crosses))