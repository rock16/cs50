#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // Prompt user for their names of type string
    string names = GetString();
    char output;
    char letter;
    
    // Prints the first letter of the user name in upper case.
    printf("%c",toupper(names[0]));
    
    // iterates over each letter of a user name looking for initials.
    for (int i = 0, n = strlen(names); i < n; i++)
    {
        letter = names[i];
        if (letter == ' ')
        {
            output = names[i + 1];
            printf("%c",(toupper(output)));
        }
        
    }
    printf("\n");
}
