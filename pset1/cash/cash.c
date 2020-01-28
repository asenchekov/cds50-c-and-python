#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
//declaring the needed variables
    int coins = 0;
    float change;

//prompt for positive value
    do
    {
        change = get_float("Change owed: \n");
    }
    while (change < 0);
//make the input a round number
    change = change * 100;
    change = round(change);
//checks how many 25 cent coins
    while (change >= 25)
    {
        change = change - 25;
        coins++;
    }
// checks how many 10 cent coins
    while (change >= 10)
    {
        change = change - 10;
        coins++;
    }
// checks how many 6 cent coins
    while (change >= 5)
    {
        change = change - 5;
        coins++;
    }
// checks how many 1 cent coins
    while (change >= 1)
    {
        change = change - 1;
        coins++;
    }
//prints the total amount of coins
    printf("%d\n", coins);
}

