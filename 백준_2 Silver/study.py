import sys
input = sys.stdin.readline
INF = 9999999

def count(A, n):
    count = 0
    for i in range(n):
        if ((A & (1 << i)) != 0):
            count += 1
    return count

def isIn(i, A):
    if ((A & (1 << (i-1))) != 0):
        return True
    else:
        return False
    
def diff(A, j):
    t = 1 << (j-2)
    return (A & (~t))

def minimum(W, D, i, A):
    minValue = INF
    minj = 1
    n = len(W) - 1
    for j in range(2, n+1):
        if(isIn(j, A)):
            m = W[i][j] + D[j][diff(A, j)]
            if ()
            
            
            
# n, m = map(int, input().split())
# mat = [[0]*(n+1) for _ in range(n+1)]
# for i in range(m):
#     u, v, w = map(int, input().split())
#     mat[u][v] = w
    
# for i in range(1, n+1):
#     print(*mat[i][1:])