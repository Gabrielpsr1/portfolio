#include <cs50.h>
#include <stdio.h>
#include <string.h>

//define the max of candidates
#define MAX 9


//struct candidate
typedef struct
{
    string name;
    int votes;
} candidate;

//array
candidate candidates[MAX];


int vote_count(string vote,candidate candidates[]);
int biggest_number(candidate candidates_list[]);
void printwinner(int winner_number,candidate candidates_list[]);

int main (int argc,string argv[])
{
    //minimum number of arguments
    if(argc < 2)
    {
        printf("./plurality [candidate...]\n");
        return 1;
    }

    // define the number of voters
   int number_of_voters = get_int("How many voters? ");

   // define the candidates
   int candidate_count = argc - 1;
   if (candidate_count > MAX)
   {
       printf("Maximum number of candidates is %i\n", MAX);
       return 2;
   }

   //names and starter votes
   for(int i = 0; i < candidate_count; i++)
   {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
   }

   //get the votes
   for(int i = 0; i < number_of_voters; i++)
   {
    string vote = get_string("who's you voting for? ");

    vote_count( vote,  candidates);
    }

    int winner_number = biggest_number(candidates);
    printwinner(winner_number, candidates);




}

int vote_count(string vote,candidate candidates_list[])
{
    for(int j = 0; j < MAX; j++)
    {
        if(strcmp(vote,candidates_list[j].name) == 0)
        {
            candidates_list[j].votes++;
            return 0;
        }
    }
    printf("this is not a candidate\n");
    return 1;
}


int biggest_number(candidate candidates_list[])
{
    int biggest_number = 0;
    for(int i = 0;i < MAX; i++)
    {
        if(biggest_number < candidates_list[i].votes)
        {
            biggest_number = candidates_list[i].votes;
        }
    }
    return biggest_number;
}

void printwinner(int winner_number,candidate candidates_list[])
{
    for(int i = 0; i<MAX ; i++)
    {
        if(winner_number == candidates_list[i].votes)
        {
            printf("%s\n", candidates_list[i].name);
        }
    }
}
