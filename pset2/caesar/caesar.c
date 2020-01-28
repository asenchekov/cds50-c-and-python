#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    //assigning th key variable with the numerical value from th input argument
    int key;
    string text;

    // make sure that th user has givern the right input format
    if (argc == 1)
    {
        printf("Please pass the Key positive numerical value as an argument\n");
        return 1;
    }
    // makes sure that argument exists
    else if (atoi(argv[1]) <= 0)
    {
        printf("Please pass the Key positive numerical value as an argument\n");
        return 1;
    }
    //cipher the text
    else
    {
        //turning the argument into integer
        key = atoi(argv[1]);
        //get input string
        text = get_string("Please input the message to cript: ");
        //iterate over evety letter of the string
        for (int i = 0; text[i] != '\0'; i++)
        {
            //checks if character is a leter or not
            if (isalpha(text[i]))
            {
                //checks if uppercase
                if (isupper(text[i]))
                {
                    text[i] = ('A' + (text[i] - 'A' + key) % 26);
                }
                //checks if lowercase
                if (islower(text[i]))
                {
                    text[i] = ('a' + (text[i] - 'a' + key) % 26);
                }
            }
        }
        //prints the ciphertext
        printf("ciphertext: %s\n", text);

    }
}