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

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(key) != 26 || !duplicate_letters(key) || only_letters(key))
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
                return false;
            }
        }
    }
    return true;
}

bool only_letters(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}

string cipher(string text, string key)
{
    int ci;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (islower(text[i]))
        {
            ci = text[i] - 'a';
            text[i] = tolower(key[ci]);
        }
        else if (isupper(text[i]))
        {
            ci = text[i] - 'A';
            text[i] = toupper(key[ci]);
        }
    }
    return text;
}
