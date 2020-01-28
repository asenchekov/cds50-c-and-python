#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    //assigning th key variable with the numerical value from th input argument
    string key;
    string text;
    char shift;

    if (argc > 2)
    {
        printf("No spaces between key literals\n");
        return 1;
    }
    if (argc == 1)
    {
        // make sure that th user has given the Key
        printf("Please enter a Key\n");
        return 1;
    }

    while (argc == 2)
    {
        key = argv[1];

        // makes sure that argument is sequence of letters
        for (int i = 0; key[i] != '\0'; i++)
        {

            if (key[i] >= '0' && key[i] <= '9')
            {
                printf("Please enter as Key only literals\n");
                return 1;
            }
        }

        if (key)
        {
            //get input string
            text = get_string("Please input the message to cript: ");

            //iterate over every letter of the string
            for (int j = 0, k = 0; text[j] != '\0'; j++)
            {

                //checks if character is a leter or not
                if (isalpha(text[j]))
                {
                    //prepares the key
                    if (key[k] != '\0')
                    {
                        shift = key[k];
                        if (isupper(shift))
                        {
                            shift -= 'A';
                        }
                        if (islower(shift))
                        {
                            shift -= 'a';
                        }

                        //checks if uppercase
                        if (isupper(text[j]))
                        {
                            text[j] = ('A' + (text[j] - 'A' + shift) % 26);
                            k++;
                        }
                        //checks if lowercase
                        if (islower(text[j]))
                        {
                            text[j] = ('a' + (text[j] - 'a' + shift) % 26);
                            k++;
                        }
                    }
                    else
                    {
                        k = 0;

                        //prepares the key
                        shift = key[k];
                        if (isupper(shift))
                        {
                            shift -= 'A';
                        }
                        if (islower(shift))
                        {
                            shift -= 'a';
                        }

                        //checks if uppercase
                        if (isupper(text[j]))
                        {
                            text[j] = ('A' + (text[j] - 'A' + shift) % 26);
                            k++;
                        }

                        //checks if lowercase
                        if (islower(text[j]))
                        {
                            text[j] = ('a' + (text[j] - 'a' + shift) % 26);
                            k++;
                        }
                    }
                }

                if (ispunct(text[j]))
                {
                }
            }
            //prints the ciphertext
            printf("ciphertext: %s\n", text);
            return 0;
            // break;
        }

        else
        {
            printf("Please enter as Key only literals\n");
            return 1;
            // break;
        }
    }
}