#ifndef ARGH_H
#define ARGH_H

#include <stdlib.h>
#include <string.h>

/*
*   Argument handlers
*/

/*
*   Concatenates arguments
*/
int argh_add(char **argh, size_t *argh_len, char **arg)
{
    if (*argh == NULL && *arg != NULL)
    {
        *argh = realloc(*argh, sizeof(*argh) + sizeof(*arg) + 2);
        strcat(*argh, " ");
        strcat(*argh, *arg);
        *argh_len += 1;
        return 0;
    }
    else if (arg != NULL)
    {
        *argh = realloc(*argh, sizeof(*arg));
        strcat(*argh, *arg);
        *argh_len += 1;
        return 0;
    }
    return 1;
}

/*
* Returns array of argumentsq
* 
*/
char **argh_extract(char **argh, size_t *argh_len, char **result)
{
    int i, j = 0;
    char *temp = (char *)malloc(sizeof(*argh));
    strcpy(temp, *argh);
    char *token = strtok(temp, " ");
    // if(result)
    // result = (char **)malloc(*argh_len);
    while (token != NULL)
    {
        result[i++] = (char *)malloc(sizeof(token));
        result[i] = token;
        token = strtok(NULL, " ");
    }
    return result;
}

int argh_size(char **argh, size_t *argh_len)
{
    return strlen(*argh) + 1;
}
#endif // ARGH_H
