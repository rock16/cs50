#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    double number;
    int coins = 0;
    
    // Promp user for input.
    do
    {
        printf("how much change is owed: ");
        number = GetDouble();
    } while (number < 0);
    int change = (number * 100);
    
    // Find the number of coins.
    if (change >= 25)
    {
        coins += (change / 25);
        change = (change % 25);
    }
    if (change >= 10)
    {
        coins += (change / 10);
        change = (change % 10);
    }
    if (change >= 5)
    {
        coins += (change / 5);
        change = (change % 5);
    }
    if (change >= 1)
    {
        coins += (change / 1);
        change = (change % 1);
    }
    printf("%i\n", coins);
}