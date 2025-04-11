import heapq
import sys

input = sys.stdin.readline

N = int(input())
p = list(map(lambda x: int(x) - 1, input().split()))
A = list(map(int, input().split()))

tree = [[] for _ in range(N)]
for i in range(N - 1):
    tree[p[i]].append(i + 1)
pq = [[-A[0], 0]]

curSum = 0
ans = []

for i in range(N):
    cur = heapq.heappop(pq)
    curSum -= cur[0]
    ans.append(curSum)
    for e in tree[cur[1]]:
        heapq.heappush(pq, [-A[e], e])

print(*ans, sep='\n')