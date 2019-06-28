#include <cs50.h>
#include <stdio.h>
#include <string.h>
char* lowercase (char* name);
int shift (char c);

int main(int argc, string argv[])
{
    // check if there is only two command line arguments
    if (argc == 2)
    {
        // check if command line argument is actually alphabets
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if ((argv[1][i] < 65) || ((argv[1][i] > 90) && (argv[1][i] < 97)) || (argv[1][i] > 122))
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    // convert to lowercase letters and store it in key
    string key = lowercase(argv[1]);
    int position = 0;
    int len = strlen(key);

    string plain = get_string("plaintext: ");
    for( int i = 0, n = strlen(plain); i < n; i++)
    {
        // if alphabets are upper case
        if (plain[i] >= 65 && plain[i] <= 90)
        {
            plain[i] = plain[i] + shift(key[position % len]);
            position = position + 1;
            if (plain[i] > 90)
            {
                plain[i] = plain[i] - 26;
            }
          }
        // if alphabets are lower case
        // different technique, as ascii cant cross 127

        if (plain[i] >= 97  && plain[i] <= 122)
        {
            int numb = plain[i] + shift(key[position % len]);

            if (numb > 122)
            {
                plain[i] = plain[i] - 26;
            }
            plain[i] = plain[i] + shift(key[position % len]);
            position = position + 1;
        }
    }
    printf("ciphertext: %s\n", plain);
    return 0;
}


// function to change it into lowercase
char* lowercase (char* name)
{
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] >= 'A' && name[i] <= 'Z')
        {
            name[i] = name[i] + 32;
        }
    }
    return name;
}

// function to create shifting values from char
int shift (char c)
{
    int b = c - 97;
    return b;
}