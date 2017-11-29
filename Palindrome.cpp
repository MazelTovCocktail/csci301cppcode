#include <stdio.h>

#include <ctype.h>

#include <string.h>

#define SIZE 100

 

int palindrome(char *string);

char *fgetstr(char *string, int n, FILE *stream);

 

int main()

{

    char input[SIZE];

    fgetstr(input, SIZE, stdin);

    if( palindrome(input) )

        printf("That is a palindrome\n");

    else

        printf("That is not a palindrome\n");

 

    return 0;

}


char *fgetstr(char *string, int n, FILE *stream)

{

    char *result;

    result = fgets(string, n, stream);

    if(!result)

        return(result);

 

    if(string[strlen(string) - 1] == '\n')

        string[strlen(string) - 1] = 0;

 

    return(string);

}


int palindrome(char *string)

{

    char forwards[SIZE];

    char backwards[SIZE];

    int i, j=0, offset=0;

    for(i=0; i<=strlen(string); i++)

        string[i] = tolower(string[i]);

    for(i=0; i<=strlen(string); i++)

    {

        if(string[i+offset] == '\0')

        {

            forwards[i] = '\0';

            break;

        }

        while(string[i+offset] < 97 || string[i+offset] > 122)

            offset++;


        if(i+offset < strlen(string))

            forwards[i] = string[i+offset];

        else

            break;

    }

    printf("Stripped: %s\n", forwards);

    for(i=strlen(forwards)-1; i>=0; i--)

    {

        backwards[j] = forwards[i];

        j++;

    }


    backwards[ strlen(forwards) ] = '\0';

    return !strcmp(forwards, backwards);

}

