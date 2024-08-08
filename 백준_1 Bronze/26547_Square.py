k = int(input())
for i in range(k):
  inp = input()
  if len(inp) == 1:
    print(inp)
    continue

  print(inp)
  for i in range(1, len(inp) - 1):
    print(inp[i], end = " " * (len(inp) - 2))
    print(inp[len(inp) - i - 1])
  print(*reversed(inp), sep = "")