#include <stdio.h>
#include <cs50.h>


int main(void)
{
// declare variables used in the loops
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

        for (j = 1; j < h; j++)
        {
            printf("%c", space);

        }

        for (int k = i; k > 0; k--)
        {
            printf("%c", hash);

        }

//prints space between the two pyramids
        printf("  ");

// draw second pyramide
        for (int l = i; l > 0; l--)
        {
            printf("%c", hash);

        }

        printf("\n");
        h--;
        i++;

    }

}