import cs50

# Declaring variables
coins = 0
change = -1

# Promp user for positive value
while change < 0:
    change = cs50.get_float("Change owed: ")
# Make the input round number
change *= 100
change = round(change)
# Check how many 25 cents coins
while change >= 25:
    change -= 25
    coins += 1
# Check how many 10 cents coins
while change >= 10:
    change -= 10
    coins += 1
# Check how many 5 cents coins
while change >= 5:
    change -= 5
    coins += 1
# Check how many 1 cent coins
while change >= 1:
    change -= 1
    coins += 1
# Prints the total amount of coins
print(coins)
