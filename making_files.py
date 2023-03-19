import random

# caz random

with open("r_10000.txt", "w") as file:
    for x in range(10000):
        file.write(f"{str(random.randint(1,10000))}\n")

with open("r_1000000.txt", "w") as file:
    for x in range(1000000):
        file.write(f"{str(random.randint(1,1000000))}\n")

with open("r_1000.txt", "w") as file:
    for x in range(1000):
        file.write(f"{str(random.randint(1,1000))}\n")

with open("r_10000000.txt", "w") as file:
    for x in range(10000000):
        file.write(f"{str(random.randint(1,10000000))}\n")


# sortate crescator

with open("s_10000000.txt","w") as file:
    for x in range(1,10000001):
        file.write(f"{str(x)}\n")

with open("s_10000.txt","w") as file:
    for x in range(1,10001):
        file.write(f"{str(x)}\n")

with open("s_1000000.txt","w") as file:
    for x in range(1,1000001):
        file.write(f"{str(x)}\n")

# descrescator
with open("re_1000.txt", "w") as file:
    for x in range(1000,0,-1):
        file.write(f"{str(x)}\n")

with open("re_10000000.txt", "w") as file:
    for x in range(10000000,0,-1):
        file.write(f"{str(x)}\n")

with open("re_10000.txt", "w") as file:
    for x in range(10000,0,-1):
        file.write(f"{str(x)}\n")

with open("re_1000000.txt", "w") as file:
    for x in range(1000000,0,-1):
        file.write(f"{str(x)}\n")
