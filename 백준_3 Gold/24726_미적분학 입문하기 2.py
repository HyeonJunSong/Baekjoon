import math

def integral(l1, l2, x):
  term1 = (l1[1] ** 2 - l2[1] ** 2) * x
  term2 = (l1[0] * l1[1] - l2[0] * l2[1]) * (x ** 2)
  term3 = ((l1[0] ** 2 - l2[0] ** 2) / 3) * (x ** 3)
  return (term1 + term2 + term3) * math.pi

def getVolume(p1, p2, p3):

  if p1[0] == p2[0] or p2[0] == p3[0]:
    if p1[1] == p3[1]:
      if p1[1] < p2[1]:
        return integral([(p3[1] - p2[1]) / (p3[0] - p2[0]), -((p3[1] - p2[1]) / (p3[0] - p2[0])) * p2[0] + p2[1]], [0, p3[1]], p3[0]) \
             - integral([(p3[1] - p2[1]) / (p3[0] - p2[0]), -((p3[1] - p2[1]) / (p3[0] - p2[0])) * p2[0] + p2[1]], [0, p3[1]], p2[0])
      else:
        return integral([0, p1[1]], [(p2[1] - p1[1]) / (p2[0] - p1[0]), -((p2[1] - p1[1]) / (p2[0] - p1[0])) * p1[0] + p1[1]], p2[0]) \
             - integral([0, p1[1]], [(p2[1] - p1[1]) / (p2[0] - p1[0]), -((p2[1] - p1[1]) / (p2[0] - p1[0])) * p1[0] + p1[1]], p2[0])
    else:
      if p1[1] < p3[1]:
        return integral([(p3[1] - p1[1]) / (p3[0] - p1[0]), -((p3[1] - p1[1]) / (p3[0] - p1[0])) * p1[0] + p1[1]], [0, p1[1]], p3[0]) \
             - integral([(p3[1] - p1[1]) / (p3[0] - p1[0]), -((p3[1] - p1[1]) / (p3[0] - p1[0])) * p1[0] + p1[1]], [0, p1[1]], p1[0])
      else:
        return integral([0, p3[1]], [(p3[1] - p1[1]) / (p3[0] - p1[0]), -((p3[1] - p1[1]) / (p3[0] - p1[0])) * p1[0] + p1[1]], p3[0]) \
             - integral([0, p3[1]], [(p3[1] - p1[1]) / (p3[0] - p1[0]), -((p3[1] - p1[1]) / (p3[0] - p1[0])) * p1[0] + p1[1]], p1[0])

  else:
    lLine = [(p2[1] - p1[1]) / (p2[0] - p1[0]), -((p2[1] - p1[1]) / (p2[0] - p1[0])) * p1[0] + p1[1]]
    rLine = [(p3[1] - p2[1]) / (p3[0] - p2[0]), -((p3[1] - p2[1]) / (p3[0] - p2[0])) * p2[0] + p2[1]]
    mLine = [(p3[1] - p1[1]) / (p3[0] - p1[0]), -((p3[1] - p1[1]) / (p3[0] - p1[0])) * p1[0] + p1[1]]

    vol = 0

    if lLine[0] < mLine[0]:
      vol += (integral(mLine, lLine, p2[0]) - integral(mLine, lLine, p1[0]))
    else:
      vol += (integral(lLine, mLine, p2[0]) - integral(lLine, mLine, p1[0]))
    
    if mLine[0] < rLine[0]:
      vol += (integral(mLine, rLine, p3[0]) - integral(mLine, rLine, p2[0]))
    else:
      vol += (integral(rLine, mLine, p3[0]) - integral(rLine, mLine, p2[0]))
    
    return vol

inp = list(map(int, input().split()))

print(getVolume(*sorted([[inp[i], inp[i + 1]] for i in [0, 2, 4]])), end = " ")
print(getVolume(*sorted([[inp[i + 1], inp[i]] for i in [0, 2, 4]])))
