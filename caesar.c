#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cypher(string text, int k);

int main(int argc, string argv[])
{
    char c = atoi(argv[1]);
    if(argc != 2 && !isalnum(c))
    {
        printf("use: ./caesar key");
        return 1;
    }

        string text = get_string("text: ");
        int k = c;
        text = cypher(text,k);
        printf("%s\n", text);



}

string cypher(string text, int k)
{

    char ci;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                ci = text[i] - 'a';
                text[i] = ((ci + k) % 26) + 'a';
            }
            else
            {
                ci = text[i] - 'A';
                text[i] = ((ci + k) % 26) + 'A';
            }
        }
    }
    return text;
}

