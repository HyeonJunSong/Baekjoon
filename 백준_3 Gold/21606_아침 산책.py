####231107
##29m 38s

import sys

sys.setrecursionlimit(300000)

N = int(input())
A = " " + input()

tree = [[] for _ in range(N + 1)]
for _ in range(N - 1):
    u, v = map(int, sys.stdin.readline().split())
    tree[u].append(v)
    tree[v].append(u)

ans = 0
def findEdges(prev, ind):
    global ans
    
    if A[ind] == "0":
        curEdges = 0
        for e in tree[ind]:
            if e == prev:
                continue
            curEdges += findEdges(ind, e)
        return curEdges
    else:
        for e in tree[ind]:
            if e == prev:
                continue
            curEdges = findEdges(ind, e)
            ans += (curEdges + 1) * (curEdges)
        return 1

rootEdge = findEdges(0, 1)
if rootEdge != 1:
    ans += (rootEdge) * (rootEdge - 1)
print(ans)