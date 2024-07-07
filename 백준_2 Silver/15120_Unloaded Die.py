inp = list(map(float, input().split()))
print("%.3f" % abs((3.5 - sum(list(map(lambda i: (i + 1) * inp[i], range(6))))) / max(inp)))