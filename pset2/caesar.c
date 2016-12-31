#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int charToCipher(int text_char, int n, int key);

int main(int argc, string argv[])
{
    // Report error if command line argument is greater than or less than 2.
    if (argc > 2 || argc < 2)
    {
        printf("error!");
        return 1;
    } 
    
    else 
    {
        // prompt user for input.
        int key = atoi(argv[1]);
        string plain_text = GetString();
        
        // Iterate over plaintext.
        for (int i = 0, n = strlen(plain_text); i < n; i++)
        {
            char text_char = plain_text[i];
            
            // prints upper case cipher text.
            if (isupper(text_char))
            {
                printf("%c", charToCipher(text_char, 65, key));
            }
            
            // prints lower case cipher text.
            else if (islower(text_char))
            {
                printf("%c", charToCipher(text_char, 97, key));
            }
            
            // prints non letter characters.
            else
            {
                printf("%c", text_char);
            }
        }
        printf("\n");
        return 0;
    }
}

// shift characters by the key.
int charToCipher(int text_char, int n, int key)
{
    int letter_pos = (text_char - n) + key;
    letter_pos %= 26;
    letter_pos += n;
    return letter_pos;
}