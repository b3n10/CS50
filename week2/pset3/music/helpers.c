// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //convert char to int is by subtracting it by '0'
    //https://stackoverflow.com/a/628766/6353682
    return ( (float) (fraction[0] - '0') / (float) (fraction[2] - '0') ) * 8;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //calculate hertz via octave
    int octave = (note[1] == '#' || note[1] == 'b') ? note[2] - '0' : note[1] - '0';
    int octave_hz = 440 / (pow(2, 4 - octave));

    //calculate hertz via first char
    int n = 0;
    if (note[0] == 'B')
    {
        n += 2;
    }
    else if (note[0] == 'G')
    {
        n -= 2;
    }
    else if (note[0] == 'F')
    {
        n -= 4;
    }
    else if (note[0] == 'E')
    {
        n -= 5;
    }
    else if (note[0] == 'D')
    {
        n -= 7;
    }
    else if (note[0] == 'C')
    {
        n -= 9;
    }

    float total_hz = octave_hz * pow(2, ( (float) (n) / (float) (12)) );

    if (note[1] == '#')
    {
        return round(total_hz * pow(2, (float) 1 / (float) 12));
    }
    else if (note[1] == 'b')
    {
        return round(total_hz / pow(2, (float) 1 / (float) 12));
    }

    return round(total_hz);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //https://stackoverflow.com/a/26609721/6353682
    if (s[0] == '\0')
    {
        return true;
    }
    return false;
}
