N = int(input())

def convert(inp):
  st, ed = inp.split()
  st = st.split(":")
  ed = ed.split(":")
  return [int(st[0]) * 60 * 60 + int(st[1]) * 60 + int(st[2]), int(ed[0]) * 60 * 60 + int(ed[1]) * 60 + int(ed[2])]
people = [convert(input()) for _ in range(N)]

peopleAt = [0 for _ in range(24 * 60 * 60 + 1)]
for e in people:
  peopleAt[e[0]] += 1
  peopleAt[e[1] + 1] -= 1

for i in range(1, len(peopleAt)):
  peopleAt[i] += peopleAt[i - 1]

print(max(peopleAt))