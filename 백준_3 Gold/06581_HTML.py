import sys

html = "".join(sys.stdin.readlines())

#연속된 공백문자, 개행문자, 탭 -> 공백
html = html.replace("\n", " ")
html = html.replace("\t", " ")
html = html.split()

#태그 바꾸기 & 개행하기
ans = [[]]
for e in html:
  if e == "<br>":
    ans.append([])
  elif e == "<hr>":
    if len(ans[-1]) != 0:
      ans.append([])
    ans[-1].append('-' * 80)
    ans.append([])
  else:
    if len(ans[-1]) + sum(list(map(lambda x: len(x), ans[-1]))) + len(e) > 80:
      ans.append([])
    ans[-1].append(e)

for e in ans:
  print(*e, sep = " ")