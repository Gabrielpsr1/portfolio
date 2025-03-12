#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_row2(int bricks);
void print_bs(int bricks);

int main(void)
{
    // get the user input
    int height;
    do
    {
        height = get_int("What's the height of the pyramid? ");
    }
    while (height <= 0 && height <= 8);

    // loop to print
    for (int j = 0; j < height; j++)
    {
        print_bs(height - j - 1);
        print_row(j + 1);
        print_bs(2);
        print_row2(j + 1);
    }
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}

void print_row2(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

// bs is blank space, not bs (you know what i mean)
void print_bs(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf(" ");
    }
}
