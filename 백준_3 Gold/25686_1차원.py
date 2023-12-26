N = int(input())

def orders(N):
  if N == 1:
    return [0]
  if N == 2:
    return [0, 1]
  if N == 3:
    return [0, 2, 1]
  
  left = [i for i in range(0, N, 2)]
  right = [i for i in range(1, N, 2)]
      
  leftOrder = orders(len(left))
  rightOrder = orders(len(right))
  
  newLeft = [left[leftOrder[i]] for i in range(len(left))]
  newRight = [right[rightOrder[i]] for i in range(len(right))]
  return newLeft + newRight

def add1(num):
  return num + 1

print(*list(map(add1, orders(N))))