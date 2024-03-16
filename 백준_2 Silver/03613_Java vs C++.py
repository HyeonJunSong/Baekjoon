
def ifJAVA(string: str):
  ifFirst = True
  for e in string:
    if ifFirst:
      if not e.isalpha() or not e.islower():
        return False
      ifFirst = False
    else:
      if not e.isalpha():
        return False
  return True

def ifCPP(string: str):
  for e in string.split("_"):
    if len(e) == 0:
      return False

    for e2 in e:
      if not e2.isalpha() or not e2.islower():
        return False
  
  return True

def JAVATOCPP(string: str):
  for e in string:
    if e.isupper():
      print("_", end = "")
      print(e.lower(), end = "")
    else:
      print(e, end = "")

def CPPTOJAVA(string: str):
  isFirst = True
  for e in string.split("_"):
    if isFirst:
      print(e, end = "")
      isFirst = False
    else:
      print(e[0].upper(), e[1:], end = "", sep = "")

string = input()
if ifJAVA(string):
  JAVATOCPP(string)
elif ifCPP(string):
  CPPTOJAVA(string)
else:
  print("Error!")