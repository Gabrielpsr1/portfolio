#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int score(string player);

int main(void)
{
    //get player's inputs
    string player_one = get_string("player 1: ");
    string player_two = get_string("player 2: ");

    int score_player_one = score(player_one);
    int score_player_two = score(player_two);

    if(score_player_one > score_player_two)
    {
        printf("Player 1 wins!\n");
    }
    else if(score_player_one < score_player_two)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score(string player)
{
    int sum = 0;
    for(int j = 0, len = strlen(player); j < len; j++)
    {
        char x = player[j];

        //change all letters to capital,so we can compare
        if(!isupper(x))
            {
                x = toupper(x);
            }

        //counts the points
        if(x == 'A' || x == 'E' || x == 'O' || x == 'N' || x == 'S' || x == 'T' || x == 'U' || x == 'L')
        {
            sum += 1;
        }
        else if( x == 'D' || x == 'G')
        {
            sum += 2;
        }
        else if( x == 'B' || x == 'C' || x == 'M' || x == 'P')
        {
            sum += 3;
        }
        else if( x == 'F' || x == 'H' || x == 'V' || x == 'W' || x == 'Y')
        {
            sum += 4;
        }
        else if( x == 'K' )
        {
            sum += 5;
        }
        else if( x == 'J' || x == 'X')
        {
            sum += 8;
        }
        else if( x == 'Q' || x == 'Z')
        {
            sum += 10;
        }
    }
    return sum;
}
