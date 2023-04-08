#함수
def product(I: int, J : int):
    if findNumOfZerosBetweenIJ(I, J) > 0:
        return '0'
    if findNumOfNegativesBetweenIJ(I, J) % 2 == 0:
        return '+'
    else:
        return '-'

def findNumOfNegativesBetweenIJ(I : int, J : int):
    if len(negatives) == 0:
        return 0
    
    #I 이상의 최소 인덱스 찾기
    st, ed = 0, len(negatives) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if negatives[mid] < I:
            st = mid + 1
        else:
            ed = mid - 1
    
    if st == len(negatives):
        I = len(negatives)
    elif ed == -1:
        I = 0
    elif negatives[st] < I:
        I = st + 1
    elif negatives[ed] < I:
        I = ed + 1
    else:
        I = ed
    
    #J 이하의 최대 인덱스 찾기
    st, ed = 0, len(negatives) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if negatives[mid] <= J:
            st = mid + 1
        else:
            ed = mid - 1
    
    if st == len(negatives):
        J = len(negatives) - 1 
    elif ed == -1:
        J = -1
    elif negatives[st] <= J:
        J = st
    elif negatives[ed] <= J:
        J = ed
    else:
        J = ed - 1
    
    return J - I + 1
    
def findNumOfZerosBetweenIJ(I : int, J : int):
    if len(zeros) == 0:
        return 0
    
    #I 이상의 최소 인덱스 찾기
    st, ed = 0, len(zeros) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if zeros[mid] < I:
            st = mid + 1
        else:
            ed = mid - 1
    
    if st == len(zeros):
        I = len(zeros)
    elif ed == -1:
        I = 0
    elif zeros[st] < I:
        I = st + 1
    elif zeros[ed] < I:
        I = ed + 1
    else:
        I = ed
    
    #J 이하의 최대 인덱스 찾기
    st, ed = 0, len(zeros) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if zeros[mid] <= J:
            st = mid + 1
        else:
            ed = mid - 1
    
    if st == len(zeros):
        J = len(zeros) - 1 
    elif ed == -1:
        J = -1
    elif zeros[st] <= J:
        J = st
    elif zeros[ed] <= J:
        J = ed
    else:
        J = ed - 1
    
    return J - I + 1

def changeNum(I : int, V : int):
    if V == 0 and numArr[I] != 0:
        if numArr[I] < 0:
            deleteNegtative(I)
        insertZero(I)
        
    elif V > 0 and numArr[I] <= 0:
        if numArr[I] == 0:
            deleteZero(I)
        else:
            deleteNegtative(I)
    
    elif V < 0 and numArr[I] >= 0:
        if numArr[I] == 0:
            deleteZero(I)
        insertNegative(I)
        
    numArr[I] = V

def insertNegative(I : int):
    #넣을 음수 위치 찾기
    st, ed = 0, len(negatives) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if negatives[mid] < I:
            st = mid + 1
        else:
            ed = mid - 1
    
    if st == len(negatives):
        newI = len(negatives)
    elif ed == -1:
        newI = 0
    elif negatives[st] < I:
        newI = st + 1
    elif negatives[ed] < I:
        newI = ed + 1
    else:
        newI = ed
    
    negatives.insert(newI, I)
            
def deleteNegtative(I : int):
    #삭제할 음수 위치 찾기
    st, ed = 0, len(negatives) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if negatives[mid] == I:
            st = mid
            break
            
        if negatives[mid] < I:
            st = mid + 1
        else:
            ed = mid - 1
    
    negatives.pop(st)

def insertZero(I : int):
    #넣을 음수 위치 찾기
    st, ed = 0, len(zeros) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if zeros[mid] < I:
            st = mid + 1
        else:
            ed = mid - 1
    
    if st == len(zeros):
        newI = len(zeros)
    elif ed == -1:
        newI = 0
    elif zeros[st] < I:
        newI = st + 1
    elif zeros[ed] < I:
        newI = ed + 1
    else:
        newI = ed
    
    zeros.insert(newI, I)
            
def deleteZero(I : int):
    #삭제할 음수 위치 찾기
    st, ed = 0, len(zeros) - 1
    while st <= ed:
        mid = (st + ed) // 2
        if zeros[mid] == I:
            st = mid
            break
            
        if zeros[mid] < I:
            st = mid + 1
        else:
            ed = mid - 1
    
    zeros.pop(st)    
    
#입력
import sys
inp = sys.stdin.readlines()

#실행
i = 0
while i < len(inp):
    N, K = map(int, inp[i][:-1].split()); i += 1
    numArr = [0] + list(map(int, inp[i][:-1].split())); i += 1
    
    negatives = []
    zeros = []
    for j in range(len(numArr)):
        if numArr[j] == 0:
            zeros.append(j)
        elif numArr[j] < 0:
            negatives.append(j)
    
    for j in range(K):
        curCommand = inp[i][:-1].split(); i += 1
        if curCommand[0] == 'C':
            changeNum(int(curCommand[1]), int(curCommand[2]))
        else:
            print(product(int(curCommand[1]), int(curCommand[2])), end = "")
    print()