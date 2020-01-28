import cs50
import sys

cypher = ""

# Check if input is correct
if len(sys.argv) > 2:
    print("No spaces between key literals")
    sys.exit(1)

    # make sure that th user has given the Key
if len(sys.argv) == 1:
    print("Please enter a Key")
    sys.exit(1)

while len(sys.argv) == 2:
    key = str(sys.argv[1])
    k = 0

    # makes sure that argument is sequence of letters
    if not key.isalpha():
        print("Please enter as Key only literals")
        sys.exit(1)

    if key:
        # get input string
        text = input("Please input the message to cript: ")

        # iterate over every letter of the string
        for b in text:
            # checks if character is a leter or not
            if k >= len(key):
                k = 0

            shift = key[k]

            if shift.isupper():
                shift = ord(shift)
                shift -= ord('A')

            elif shift.islower():
                shift = ord(shift)
                shift -= ord('a')

            # checks if uppercase
            if b.isupper():
                cypher += chr((ord('A') + (ord(b) - ord('A') + shift) % 26))
                k += 1

            # checks if lowercase
            elif b.islower():
                cypher += chr((ord('a') + (ord(b) - ord('a') + shift) % 26))
                k += 1

            else:
                cypher += b

        # prints the ciphertext
        print("ciphertext: ", cypher)
        sys.exit(0)
        break

    else:
        print("Please enter as Key only literals")
        sys.exit(0)
        break