// cash.c
// Parthiban Bala
// Program gets imput from the user, which is a float value in dollars
// program will give minimum number of coins needed to dispense the cash

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    // initiating cash in dollars, and getting a valid amount through while loop
    float cash = -1;
    while (cash < 0)
    {
       cash = get_float("Change owed: "); 
    } 
    
    // converting cash into cents
    int coins = round(cash * 100);
    // initiating counter, with value 0, which counts number of coins needed
    int counter = 0;
    //calculating number of quarters needed; once value is less than 25, will go to next step
    while (coins >= 25)
    {
        coins = coins - 25;
        counter += 1;
    }
    //calculating number of dimes needed; once value is less than 10, will go to next step
    while (coins >= 10)
    {
        coins = coins - 10;
        counter += 1;
    }
    //calculating number of nickels needed; once value is less than 5, will go to next step
    while (coins >= 5)
    {
        coins = coins - 5;
        counter += 1;
    }
    //calculating number of pennies needed; once value is 0, will go to next step
    while (coins >= 1)
    {
        coins = coins - 1;
        counter += 1;
    }
    // print the minimum number of coins needed
    printf("%i\n", counter);    
}
