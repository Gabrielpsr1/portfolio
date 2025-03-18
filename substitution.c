#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_letters(string key);
bool duplicate_letters(string key);
string cipher(string text, string key);

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2 || only_letters(key))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(key) != 26 || !duplicate_letters(key))
    {
        printf("Key must have 26 different letters.\n");
        return 1;
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", cipher(text, key));
}

bool duplicate_letters(string key)
{
    for (int i = 0,len = strlen(key); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                return 1;
            }
        }
    }
    return 0;
}

bool only_letters(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            return 2;
        }
    }
    return 0;
}

string cipher(string text, string key)
{
    int ci;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (islower(text[i]))
        {
            ci = text[i] - 'a';
            key[ci] = tolower(key[ci]);
            text[i] = key[ci];
        }
        if (isupper(text[i]))
        {
            ci = text[i] - 'A';
            key[ci] = toupper(key[ci]);
            text[i] = key[ci];
        }
    }
    return text;
}
