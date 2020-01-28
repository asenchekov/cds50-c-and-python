// Helper functions for music

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

int toneCalculator(int i, string a, string b, int c, float d);

int octaveCalculator(int a, int b, float c, string d, float e);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x, y;
    x = fraction[0] - '0';
    y = fraction[2] - '0';

    // Checks if denominator is equal to 8 and returns the numerator
    if (y == 8)
    {
        return x;
    }
    // Otherwise returns 8 devided by the denominator
    else
    {
        return 8 / y;
    }

}


// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Declaring the variables
    int octave;
    int A4 = 4;

    // Checks if note has 2 characters
    if (note[2] == '\0')
    {
        // Turns the octave to a number
        octave = note[1] - '0';
        // Calculates the octave
        return octaveCalculator(A4, octave, 440, note, 1);
    }
    else
    {
        octave = note[2] - '0';
        return octaveCalculator(A4, octave, 440, note, 1);
    }
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // Checks if s is an empty string
    if (s[0] == '\0')
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Recursive function which calculates the octave for the note
int octaveCalculator(int a, int b, float c, string d, float e)
{
    //Declaring string of notes to check which note is from this octave
    string NOTES = "#C#D#EF#G#A#B";

    // Stops recursion
    if (a == b)
    {
        // Checks if flat
        if (d[1] == 'b')
        {
            e /= 12;
            c /= pow(2, e);

            return toneCalculator(0, d, NOTES, 10, c);
        }

        // Checks if sharp
        if (d[1] == '#')
        {
            e /= 12;
            c *= pow(2, e);

            return toneCalculator(0, d, NOTES, 10, c);
        }

        else
        {
            return toneCalculator(0, d, NOTES, 10, c);
        }
    }

    else
    {
        if (a < b)
        {
            return octaveCalculator(a + 1, b, c * 2, d, e);
        }

        else
        {
            return octaveCalculator(a - 1, b, c / 2, d, e);
        }
    }
}

// Calculates the frequency of the note
int toneCalculator(int i, string a, string b, int c, float d)
{
    if (a[0] == b[i])
    {
        float x = 1;

        if (i < c)
        {
            x /= 12;
            d /= pow(2, x);
            return toneCalculator(i, a, b, c - 1, d);
        }

        if (i > c)
        {
            x /= 12;
            d *= pow(2, x);
            return toneCalculator(i, a, b, c + 1, d);
        }

        else
        {
            return round(d);
        }
    }

    else
    {
        return toneCalculator(i + 1, a, b, c, d);
    }
}