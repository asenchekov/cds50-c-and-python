#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int main(void) {
    int octave;
    int A4 = 4;
    int freq;
    string note = "C4";
    string NOTES = "C#D#EF#G#A#B";
    int tone;

    int toneCalculator(int i, string a, string b, float c, float d);

    int octaveCalculator(int a, int b, float c, string d, float e);

    if (note[2] == '\0')
    {
        octave = note[1] - '0';
        freq = octaveCalculator(A4, octave, 440, note, 1);
    }
    else
    {
        octave = note[2] - '0';
        freq = octaveCalculator(A4, octave, 440, note, 1);
    }

    tone = toneCalculator(0, note, NOTES, 10, freq);

    printf("The Octave is at %dHz\n", tone);
    return 0;
}

int octaveCalculator(int a, int b, float c, string d, float e) {
    if (a == b)
    {
        if (d[1] == 'b')
        {
            e /= 12;
            c /= pow(2, e);
            return floor(c);
        }

        if (d[1] == '#')
        {
            e /= 12;
            c *= pow(2, e);
            return floor(c);
        }
        else {
            return c;
        }
    }
    else
    {
        if (a < b) return octaveCalculator(a + 1, b, c * 2, d, e);
        if (a > b) return octaveCalculator(a - 1, b, c / 2, d, e);
    }
    return 1;
}

int toneCalculator(int i, string a, string b, float c, float d) {
    if (a[0] == b[i])
    {
        i++;

        if (i < c)
        {
            c -= i;
            c /= 12;
            d /= pow(2, c);
            return floor(d);
        }
        else
        {
            c = i - c;
            c /= 12;
            d *= pow(2, c);
            return floor(d);
        }
    }
    else
    {
        return toneCalculator(i + 1, a, b, c, d);
    }
}