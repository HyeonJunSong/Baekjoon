
poem = input()

space = int(input())
alph = list(map(int, input().split()))

before = '#'
for e in poem:
  if before == e: continue
  before = e
  
  if ord('A') <= ord(e) <= ord('Z'):
    if alph[ord(e) - ord('A')] <= 0:
      print(-1)
      exit(0)
    alph[ord(e) - ord('A')] -= 1
    
  elif ord('a') <= ord(e) <= ord('z'):
    if alph[ord(e) - ord('a')] <= 0:
      print(-1)
      exit(0)
      
    alph[ord(e) - ord('a')] -= 1
  else:
    if space <= 0:
      print(-1)
      exit(0)
    space -= 1

poem = poem.split()
before = -1
for e in poem:
  
  if ord('A') <= ord(e[0]) <= ord('Z'):
    if before == e: continue
    before = ord(e[0]) - ord('A')
    
    if alph[ord(e[0]) - ord('A')] <= 0:
      print(-1)
      exit(0)
    alph[ord(e[0]) - ord('A')] -= 1
    
  elif ord('a') <= ord(e[0]) <= ord('z'):
    if before == e: continue
    before = ord(e[0]) - ord('a')

    if alph[ord(e[0]) - ord('a')] <= 0:
      print(-1)
      exit(0)
      
    alph[ord(e[0]) - ord('a')] -= 1

for e in poem:
  print(e[0].upper(), end="")
