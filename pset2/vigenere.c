#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Create two prototype.
int charToCipher(int text_char, int n, int key);
int keyword(int size, int index, char word[]);

int main(int argc, string argv[])
{
    // check for command line arguments greater than 2 or less than 2.
    if (argc > 2 || argc < 2)
    {
        printf("error!");
        return 1;
    }
    // complains and exit if the second argument is not alphabet.
    for (int j = 0, k = strlen(argv[1]); j < k; j++)
    {
        if (!isalpha(argv[1][j]))
        {
            printf("Give me only alphabet\n");
            return 1;
        }
    }
    
    int keyword_size = strlen(argv[1]), keyword_idx = 0;
    // Prompt user for input
    string plain_text = GetString();

    // Iterate over each character of the plaintext.
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        char text_char = plain_text[i];
        // find and prints cipher text of upper case letters.
        if (isupper(text_char))
        {
            int key = keyword(keyword_size, keyword_idx, argv[1]);
            printf("%c", charToCipher(text_char, 65, key));
            keyword_idx++;
        }
        
        // Finds and prints cipher text of lower case letters.
        else if (islower(text_char))
        {
            int key = keyword(keyword_size, keyword_idx, argv[1]);
            printf("%c", charToCipher(text_char, 97, key));
            keyword_idx++;
        }
        
        // print non letter characters.
        else
        {
            printf("%c", text_char);
        }
        
    }
    printf("\n");
    return 0;
}

// shift characters by the key.
int charToCipher(int text_char, int n, int key)
{
    int letter_pos = (text_char - n) + key;
    letter_pos %= 26;
    letter_pos += n;
    return letter_pos;
}

// change keywords to key.
int keyword(int size, int index, string word)
{
    int i = index % size;
    if (isupper(word[i]))
    {
        return word[i] - 65;
    }
    else
    {
        return word[i] - 97;
    }
}