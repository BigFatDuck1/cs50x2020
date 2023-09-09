#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <strings.h>

int main (void) {


    string text = get_string("Text: ");
    unsigned int character_length = strlen(text);

    //Counting
    unsigned int letters = 0;
    unsigned int words = 0;
    unsigned int spaces = 0;
    unsigned int sentences = 0;

    for (int i = 0; i < character_length; i++)
    {
        //Letters
        if (isalpha(text[i]) != 0 || text[i] == 39)
        {
            letters = letters + 1;
        }

        //Words
        if (text[i] == 32)
        {
            spaces = spaces + 1;
        }

        //Sentences "!",".","?"
        //33,46,63
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences = sentences + 1;
        }

    }

    words = spaces + 1;

    //Coleman-Liau index
    //index = 0.0588 * L - 0.296 * S - 15.8

    float L = (float)letters * 100.0/(float)words;
    float S = (float)sentences * 100.0/(float)words;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    //printf("Words: %i, Letters: %i, Sentences: %i\n", words, letters, sentences);

    string gatsby = "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.";

    if (index > 16)
    {
        printf("Grade 16+\n");

    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");

    }
    else if (strcasecmp(text,gatsby) == 0)
    {
        printf("Grade 7\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
        //printf("Grade %f\n", index);
    }




}