import cs50
import sys

cypher = []

# make sure that th user has given the right input format
if len(sys.argv) == 1:
    print("Please pass the Key positive numerical value as an argument")
    sys.exit(1)

# makes sure that argument exists
elif int(sys.argv[1]) <= 0:
    print("Please pass the Key positive numerical value as an argument\n")
    sys.exit(1)

# cipher the text
else:
    # turning the argument into integer
    key = int(sys.argv[1])
    # get input string
    text = input("Please input the message to cript: ")

    # iterate over evety letter of the string
    for c in text:
        # checks if character is a leter or not
        if c.isalpha():
            # checks if uppercase
            if c.isupper():
                c = (ord('A') + (ord(c) - ord('A') + key) % 26)
                cypher.append(chr(c))
            # checks if lowercase
            else:
                c = (ord('a') + (ord(c) - ord('a') + key) % 26)
                cypher.append(chr(c))
        else:
            cypher.append(c)

    # prints the ciphertext
    print("ciphertext: ", end="")
    for a in cypher:
        print(a, end="")
    print()
