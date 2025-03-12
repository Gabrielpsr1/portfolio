#include <cs50.h>
#include <stdio.h>

// sorry about any grammar problem,english is my second language

int main(void)
{
    // get the cash input
    int cash;

    do
    {
        cash = get_int("change onwed: ");
    }
    while (cash < 0);

    int number_coins = 0;         // number of coins necessary for the change
    int coins[] = {25, 10, 5, 1}; // array of the 4 possible coins in descending order

    // loop that will discover the number of coins necessary

    for (int i = 0; i < 4; i++)
    {
        number_coins += cash / coins[i];
        cash = cash % coins[i];
    }

    printf("the minimum number of coins is: %i \n", number_coins);
}
