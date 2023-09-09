from cs50 import get_int

pheight = 0


while True: 
    pheight = get_int("Height: ")
    if pheight < 9 and pheight > 0:
        break

p = pheight

for i in range(1,p + 1):

    for j in range(1, pheight - i + 1): #Numer of spaces
        print(" ", end='')

    for k in range(1,i+1): #Number of hashes
        print("#", end='')

    print("  ", end='')

    for l in range(1,i+1): #hash 2
        print("#", end='')

    print()

