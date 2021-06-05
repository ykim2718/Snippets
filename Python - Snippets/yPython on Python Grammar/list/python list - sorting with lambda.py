yText = "The tree is not felled by the first flow."
yList = yText.split()
yListNew = sorted(yList, key=lambda x: len(x), reverse=True)
print(yListNew)
