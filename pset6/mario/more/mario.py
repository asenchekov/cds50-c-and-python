import cs50

# Getting the number from the user
h = -1
i = 0
while h < 0 or h > 23:
    h = cs50.get_int("Positive number please, not bigger than 23:")
# Starting to draw the pyramide
while h > 0:
    # Drawing spaces first
    for j in range(h - 1):
        print(' ', end="")
    # Drawing the hashes
    for k in range(i + 1):
        print('#', end="")
    # Printing space between
    print('  ', end="")
    # Prints second pyramide
    for k in range(i + 1):
        print('#', end="")
    print()
    # Adjusting the values
    h -= 1
    i += 1