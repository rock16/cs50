#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int row = 2;
    
    do
    {
        printf("height: ");
        height = GetInt();
    } while ((height < 0) || (height > 23));
    
    // Initialize a variable used for left aligning the printout.
    int indent = height;
    
    // Iterate over each collumn(height).
    for (int i = 0; i < height; i++)
    {
        // Create indentation for each line
        for (int t = indent; t > 1; t--)
        {
            printf(" ");
        }
        
        indent--;
        
        // Print the number of # on each row.
        for (int j = 0; j < row; j++)
        {
            printf("#");
        }
        printf("\n");
        row++;
    }
}