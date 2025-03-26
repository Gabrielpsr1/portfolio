#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int diff;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[], int i);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks, i);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k]))
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[], int i)
{
    for (int j = 0; j < candidate_count; j++)
    {
        preferences[i][j] = ranks[j];
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // para fazer os pares o primeirro e o segundo for
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int l = i + 1; l < candidate_count; l++)
        {
            // contar os pontos de cada um
            int par_um = 0;
            int par_dois = 0;

            // para ciclar os eleitores
            for (int j = 0; j < voter_count; j++)
            {
                // ciclar o ranking
                for (int k = 0; k < candidate_count; k++)
                {
                    //
                    if (preferences[j][k] == i)
                    {
                        par_um++;
                    }
                    else if (preferences[j][k] == l)
                    {
                        par_dois++;
                    }
                }
            }
            if(par_um > par_dois)
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = l;
                pairs[pair_count - 1].diff = i - l;
            }
            else if(par_um < par_dois)
            {
                pair_count++;
                pairs[pair_count - 1].winner = l;
                pairs[pair_count - 1].loser = i;
                pairs[pair_count - 1].diff = l - i;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair maior;
    pair trocar;
    int j;
    for(int i = 0; i < pair_count - 1; i++)
    {
        for( j = i + 1;j < pair_count;j++)
        {
            if(pairs[i].diff < pairs[j].diff)
            {
                maior = pairs[j];
                trocar = pairs[i];
            }
        }
        pairs[i] = maior;
        pairs[j] = trocar;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i< pair_count; i++)
    {
        
    }
    return;
}


// Print the winner of the election
void print_winner(void)
{
    // TODO estabilizar a coluna e ciclar as linha procurando qual n tem falso
    for(int i = 0; i< candidate_count; i++)
    {
        for(int j = 0;j < candidate_count; j++)
        {
            if(locked[j][i] == true)
            {
                break;
            }
        }
        printf("the winner is %s", candidates[i]);
    }
    return;
}
