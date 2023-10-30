import sys
S, E, Q = sys.stdin.readline().split()

entrance = set()
finish = set()

chats = sys.stdin.readlines()

for e in chats:
  time, person = e.split()
  if time <= S:
    entrance.add(person)
  elif E <= time <= Q:
    finish.add(person)

print(len(entrance.intersection(finish)))
