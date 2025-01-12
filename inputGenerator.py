from random import randint

numbersCount = 2**25
numbers = []
for i in range(numbersCount):
    # numbers.append(randint(-1 * 2**31, 2**31 - 1))
    numbers.append(randint(-1 * 2**30, 2**30 - 1))

inputFile = open("cmake-build-debug/benchmark-starter/input.txt", "w")
inputFile.write(f"{numbersCount}\n")
inputFile.write(" ".join(map(str, numbers)))
