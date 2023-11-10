N,K = input().split()
K = int(K) % 6
if (N == '0' and K == 1) or (N == '1' and K == 5) or (N == '1' and K == 0):
  print("HS")
else:
  print("YG")