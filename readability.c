#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>



int words(string str);
int letters(string str);
int sentences(string str);
void print(float index);


int main(void)
{
    string str = get_string("text: ");
    int words_count = words(str);
    int letters_count = letters(str);
    int sentences_count = sentences(str);

    //calculate the index
    float l = letters_count/words_count;
    float s = sentences_count/words_count;
    float index = 0.0588 * l - 0.296 * s - 15.8;

    //print the results
    print(index);


}





//FUNCTIONS

void print(float index)
{
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i",(int) round(index));
    }
}

// count words
int words(string str)
{
    int words_count = 1;
    for(int i = 0,len = strlen(str); i < len; i++)
    {
        if(str[i] == ' ')
        {
            words_count += 1;
        }
    }
    return words_count;
}

//count letters
int letters(string str)
{
    int letters_count = 0;
    for(int i = 0,len = strlen(str); i < len; i++)
    {
        if(isalpha(str[i]))
        {
            letters_count += 1;
        }
    }
    return letters_count;
}


//count sentences
int sentences(string str)
{
    int sentences_count = 0;
    for(int i = 0,len = strlen(str); i < len; i++)
    {
        if(str[i] == '.' || str[i] == '!' || str[i] == '?' || str[i] == ';')
        {
            sentences_count += 1;
        }
    }
    return sentences_count;
}


