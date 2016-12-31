#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt the user for the number of minutes
    printf("minutes: ");
    int minutes = GetInt();
    
    // Finds the number of gallons.
    int bottles = (minutes * 192) / 16;
    
    printf("bottles: %i\n", bottles);
}