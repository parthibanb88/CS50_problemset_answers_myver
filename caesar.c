#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check if there is only two command line arguments
    if (argc == 2)
    {
        // check if command line argument is actually a number with ascii help
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (argv[1][i] < 48 || argv[1][i] > 57)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // re print the number
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
            {
              printf("%i", argv[1][i] - 48);
            }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // convert key into int, and make it a number less than 26
    int key = atoi(argv[1]);
    key = key % 26;

    // get input
    string plain = get_string("plaintext: ");
    for( int i = 0, n = strlen(plain); i < n; i++)
    {
        // if alphabets are upper case
        if (plain[i] >= 65 && plain[i] <= 90)
        {
            plain[i] = plain[i] + key;
            if (plain[i] > 90)
            {
                plain[i] = plain[i] - 26;
            }
          }
        // if alphabets are lower case
        // different technique, as ascii cant cross 127

        if (plain[i] >= 97  && plain[i] <= 122)
        {
            int numb = plain[i] + key;
            if (numb > 122)
            {
                plain[i] = plain[i] - 26;
            }
            plain[i] = plain[i] + key;
        }
    }
    printf("ciphertext: %s\n", plain);
    return 0;
}
