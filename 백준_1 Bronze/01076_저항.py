colors = ["black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white"]
num = ""

inpColors = []
inpColors.append(input())
inpColors.append(input())
inpColors.append(input())

for i in range(10):
    if colors[i] == inpColors[0]:
        num += str(i)

for i in range(10):
    if colors[i] == inpColors[1]:
        num += str(i)

num = int(num)

for i in range(10):
    if colors[i] == inpColors[2]:
        num = num * (10 ** i)

print(num)
