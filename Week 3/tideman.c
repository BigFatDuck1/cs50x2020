#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX]; //false means i is not more popular than j

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; //Array that contains all the struct pair

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool check_cycle(int next_node, int starting_node);


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
    int voter_count = get_int("Number of VOTERS: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) //if vote() returns false, print "invalid vote"
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

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
    int v = false;

    for (int i  = 0; i < candidate_count; i++)
    { /*j is rank, e.g.
    Voter 1:
    Ranked 1: John
    In this case, the 1 in ranked 1 is j, j = 0*/
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; //i gets the candidate index
            return true;
            /*ranks is an array that stores the ranking
            e.g.
                ranks[2] :
                ranks[0 (ranked first)] = candidate John (index 0)
                ranks[1] = candidate Charlie (index 3)
                .
                .
                .
                */
            v = true;
        }


    }

    return v;



}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    // Store in 2D array preferences[][]
    //preferences[alice][bob] means the square where alice more popular than bob
    //preferences[alice][bob] = 2 means 2 people prefer alice to bob

    //ranks[0] = 2 means ranked first is candidate 2 (e.g. John)

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
            {
                //For each voter:
            //Start with rank 1st vs all other ranks
            int initial = ranks[i];
            int next = ranks[j];
            preferences[initial][next] += 1;
            }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int k = 0; k < candidate_count; k++)
    {
        for (int p = k + 1; p < candidate_count; p++)
        {
            //Three checking conditions: preferences[k][p] vs. preferences [p][k]
            if (preferences[p][k] == preferences[p][k])
            {
                //Just an empty block, like PASS in python
            }
            if (preferences[p][k] > preferences[k][p])
            {
                pairs[pair_count].winner = p;
                pairs[pair_count].loser = k;
                pair_count += 1;
            }
            if (preferences[k][p] > preferences[p][k])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = p;
                pair_count += 1;
            }
        }
    }

    //pair_count += 1; This counts the number of pairs
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //preferences[winner][loser] returns the strength of the victory
    //sort pairs[], which contains struct pair [winner, loser]

    /*--- 1. For each element in pairs[], find out its corresponding strength
    To do so, find that element again in preferences array
    i.e. preferences[winner][loser]
    and to get the right [winner][loser] pair, go back to the pairs[] array ---*/

	//This array contains all the strength of each pair
	int strength_array[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        strength_array[i] = preferences[pairs[i].winner][pairs[i].loser];
    } //Populate strength_array

    /**--- 2. Sorting: Each index in strength_array[] corresponds to each index in pairs[] array
    Sort strength_array first, then move each element in pairs[] array the same way ---*/

    int didnt_swap = 0;

    while (didnt_swap < pair_count)
    {
    	for (int l = 0; l < pair_count; l++)
    	{
    		if (strength_array[l] < strength_array[l+1]) //Push the smaller number forward (swap)
    		{
    			//Step 1: sort the strength_array[]
    			int temp_smaller = strength_array[l];
    			int temp_larger = strength_array[l+1];
    			strength_array[l] = temp_larger;
    			strength_array[l+1] = temp_smaller;

    			//Step 2: Make the pairs[] array copy the movement
    			pair pair_smaller = pairs[l];
    			pair pair_larger = pairs[l+1];
    			pairs[l] = pair_larger;
    			pairs[l+1] = pair_smaller;

    		}
    		else if (strength_array[l] >= strength_array[l+1]) //No need to swap
    		{
    			didnt_swap += 1;
    		}
    	}
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

	for (int i = 0; i < pair_count; i++) //iterate through each element in pairs[]
	{

		if (check_cycle(pairs[i].loser,pairs[i].winner) == false) //The starting node is pairs[i].winner, the next node is pairs[i].loser
		{
			//Convert each pair to true
			locked[pairs[i].winner][pairs[i].loser] = true;
			//Add a checking condition to make sure a cycle is not created
		}

		if (check_cycle(pairs[i].loser,pairs[i].winner) == true)
		{
			locked[pairs[i].winner][pairs[i].loser] = false;
		}

	}

    return;
}

bool check_cycle(int next_node, int starting_node)
{

	bool b = false; //return TRUE: cycle present
					//return FALSE: cycle not present

	if (next_node == starting_node)
		{
			b = true;
		}

	for (int j = 0; j < candidate_count; j++)
	{



		if (locked[next_node][j] == true)
		{
			if (check_cycle(j,starting_node) == true)
			{
				b = true;
			}

			 //Recursion
		}

	}

	//If the next node is not connected to anything i.e. locked[next_node][<any other node>]=FALSE

	return b; //return false = No cycle


}


// Print the winner of the election
void print_winner(void)
{

    int false_count = 0;

    for (int i = 0; i < candidate_count; i++) 
    {
        for (int j = 0; j < candidate_count; j++)
            //If it is stronger than someone else, check if it is the source
            if (locked[i][j] == true) 
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[k][i] == false) 
                    {
                        false_count += 1;
                    }

                    //If all candidates return false, means no one is stronger than the current candidate
                    if (false_count == candidate_count)
                    {
                        printf("Winner: %s\n", candidates[i]);
                        false_count = 0; //reset false_count to 0
                        break;
                    }
                }
            }
    }

	
    return;
}


