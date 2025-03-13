#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digits_count(long card_number);
int two_first_digits(long card_number , int digits);
int multiplicationf(long card_number);
int sumf(long card_number);
int verification(int sum,int multiplication);
void print_verify(int digits,int boolean,int two_digits);

int main(void)
{

    long card_number = get_long("card number: ");
    int digits = digits_count(card_number);
    int multiplication = multiplicationf(card_number);
    int sum = sumf(card_number);
    int boolean = verification(sum,multiplication);
    int two_digits = two_first_digits(card_number ,digits);

    printf("%i\n", two_digits);
    printf("%i\n", digits);
    print_verify(digits,boolean,two_digits);





}


//functions

int digits_count(long card_number)
{
    int digits = 0;
    while(card_number > 0)
    {
        card_number /= 10;
        digits++;
    }
    return digits;
}

int two_first_digits(long card_number , int digits)
{
    int two_digits = 0;
    two_digits = card_number / (long)pow(10, digits - 2);
    return two_digits;
}

int multiplicationf(long card_number)
{
    int multiplication = 0;
    int multiplication_sum = 0;
    while(card_number > 0)
    {
        card_number /= 10;
        multiplication = (card_number % 10) * 2;
        if(multiplication >=10 )
        {
            multiplication = (multiplication / 10) + (multiplication % 10);
        }
        multiplication_sum += multiplication;
        card_number /= 10;
    }
    return multiplication_sum;
    }

int sumf(long card_number)
{
        int sum = 0;
        int sum_sum = 0;
        while(card_number > 0)
        {
            sum = card_number % 10;
            sum_sum += sum;
            card_number /= 100;
        }
        return sum_sum;
}

int verification(int sum,int multiplication)
{
    if((sum + multiplication) % 10 == 0)
    {
        return 1;// used int because bool does not exist in standard C,so I did what I could
    }
    else
    {
        return 0;
    }
}

void print_verify(int digits,int boolean,int two_digits)
{
    if((digits == 13 || digits == 15 || digits == 16) && boolean == 1)
    {
        if(digits == 15 && (two_digits = 37 || two_digits == 34))
        {
            printf("AMEX\n");
        }
        else if(digits == 16 && two_digits<=55 && two_digits >= 51)
        {
            printf("MASTERCARD\n");
        }
        else if(digits == 13 || (digits == 16 && two_digits<=49 && two_digits >= 40))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
