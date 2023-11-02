import math
N = int(input())
print(math.ceil((3 * math.ceil(N / 3) - N + 1) / 2) * (math.ceil(N / 2) - math.ceil(N / 3)) + 3 * (math.ceil((math.ceil(N / 2) - math.ceil(N / 3)) / 2) - 1) * (math.ceil((math.ceil(N / 2) - math.ceil(N / 3)) / 2)) // 2 + (1 + ((3 * math.ceil(N / 3) - N + 1) + 1) % 2) * (math.floor((math.ceil(N / 2) - math.ceil(N / 3)) / 2)) + 3 * (math.floor((math.ceil(N / 2) - math.ceil(N / 3)) / 2) - 1) * (math.floor((math.ceil(N / 2) - math.ceil(N / 3)) / 2)) // 2)
