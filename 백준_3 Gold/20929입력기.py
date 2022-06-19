import random

N = int(input())


A = []
for i in range(N):
    A.append(random.randrange(1, 999999999))
A.sort()


B = []
for i in range(N):
    B.append(random.randrange(1, 999999999))
B.sort()

C = []
for i in A:

    C.append(i)
for i in B:
    C.append(i)

C.sort()

while(True):
    inpList = input().split(' ')
    
    if inpList[0] == 'a':
        print(A[int(inpList[1])])
    elif inpList[0] == 'b':
        print(B[int(inpList[1])])
    else:
        break

print("정답공개!")
print(A)
print(B)
print(C)

print(C[N-1])

