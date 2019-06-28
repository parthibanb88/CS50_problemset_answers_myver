// mario.c (less)
// Parthiban Bala
// Program gets imput from the user, height, which should be a positive int from 1 to 8
// then it prints a stairs of similar height, with base having full hashes and 
// top having epmty spaces followed by hash, producing a staircase

#include <stdio.h>
#include <cs50.h>

int main (void)
{
    // initialize height as 0, to be modified with user input
    int height = 0;
    
    // loop to get user iput that is between 1 and 8 including them
    while (height < 1 || height > 8)
    {
        height = get_int("Height :");
    }
    
    // initialising space and height; they are the number of empty spaces and 
    // number of hashes needed for each line
    int space = height - 1;
    int hash = 1;
    
    // loop to perofrm the lines of printing space and hash 
    while (hash <= height)
    {
        // loop to print empty spaces in a line
        int i = 0;
        for (i = 0; i < space; i++)
        {
            printf(" ");
        }
        // loop to print hashes in a line
        i = 0;
        for (i = 0; i < hash; i++)
        {
            printf("#");
        }
        
        // go to next line for printing; change values of hash and space for next line
        printf("\n");
        hash += 1;
        space -= 1;
    }
}
