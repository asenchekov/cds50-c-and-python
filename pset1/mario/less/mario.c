#include <stdio.h>
#include <cs50.h>


int main(void)
{
// declaring variables used in the loops
    int h = 0;
    char hash = '#';
    char space = ' ';
    int j;
    int i = 1;

//check if integer is positive and lower than 24
    do
    {
        h = get_int("Positive number please, not bigger than 23: \n");

        while (h >= 24)
        {
            h = get_int("Positive number please, not bigger than 23: \n");
        }
    }
    while (h < 0);

//draw the pyramide
    while (h > 0)
    {

//drawing spaces first
        for (j = 1; j < h; j++)
        {
            printf("%c", space);

        }
//drawing actual pyramide
        for (int k = i + 1; k > 0; k--)
        {
            printf("%c", hash);

        }

        printf("\n");
        h--;
        i++;

    }

}