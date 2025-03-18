#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cypher(string text, int k);
bool only_digits(string argvector);

int main(int argc, string argv[])
{
    string argvector = argv[1];

    if (argc != 2 || only_digits(argvector))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("text: ");
    int k = atoi(argv[1]);
    text = cypher(text, k);
    printf("ciphertext: %s\n", text);
}

bool only_digits(string argvector)
{
    for (int i = 0, len = strlen(argvector); i < len; i++)
    {
        if (argvector[i] < '0' || argvector[i] > '9')
        {
            return 2;
        }
    }
    return 0;
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
