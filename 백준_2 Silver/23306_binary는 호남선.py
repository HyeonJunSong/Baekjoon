N = int(input())

print("? 1", flush=True)
st = int(input())

print(f"? {N}", flush=True)
ed = int(input())

if st < ed:
  print("! 1", flush=True)
elif st > ed:
  print("! -1", flush=True)
else:
  print("! 0", flush=True)