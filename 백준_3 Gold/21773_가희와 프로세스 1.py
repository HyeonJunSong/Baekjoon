import heapq
import sys

T, n = map(int, sys.stdin.readline().rstrip().split())

processes = []
for i in range(n):
    A, B, C = map(int, sys.stdin.readline().rstrip().split())
    heapq.heappush(processes, [-1 * C, A, B])

for i in range(T):
    curProcess = heapq.heappop(processes)
    print(curProcess[1])
    curProcess[2] -= 1
    curProcess[0] += 1
    if curProcess[2] != 0:
        heapq.heappush(processes, curProcess)
