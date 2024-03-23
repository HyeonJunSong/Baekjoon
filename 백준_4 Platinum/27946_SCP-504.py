import sys

N, M = map(int, sys.stdin.readline().split())
dictionaries = [list(sys.stdin.readline().rstrip()) for _ in range(N)]
words = [sys.stdin.readline().rstrip() for _ in range(M)]

for e in dictionaries:
  appeared = set()
  for i in range(len(e)):
    if e[i] in appeared:
      e[i] = '?'
    else:
      appeared.add(e[i])
  
  while e[-1] == '?':
    e.pop()

tri = {}
for word in dictionaries:
  curTri = tri
  
  for letter in word:
    if letter not in curTri:
      curTri[letter] = {}
    curTri = curTri[letter]
  
  if '!' in curTri:
    curTri['!'] += 1
  else:
    curTri['!'] = 1

for word in words:
  curTri = tri
  ans = 0
  appeared = set()
  for e in word:
    if e in curTri:
      curTri = curTri[e]
      if '!' in curTri:
        ans += curTri['!']
      appeared.add(e)
    elif e in appeared and '?' in curTri:
      curTri = curTri['?']
      if '!' in curTri:
        ans += curTri['!']
    else:
      break
  
  sys.stdout.write("%d\n" % ans)