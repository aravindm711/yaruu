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
char **argh_add(char **argh, size_t *argh_len, char *arg)
{
    if (argh == NULL)
    {
        argh = (char **)malloc(2 * sizeof(char *));
        argh[0] = (char *)malloc(sizeof(char) * 6);
        argh[0] = (char *)"rsync";
        argh[1] = (char *)malloc(strlen(arg) + 1);
        strcpy(argh[0], arg);
        *argh_len += 1;
        return argh;
    }
    if (arg != NULL)
    {
        *argh_len += 1;
        const int size = *argh_len;
        argh = (char **)realloc(argh, sizeof(char *) * (size));
        argh[size - 1] = arg;
        return argh;
    }
    return (char **)0;
}

/*
* Returns array of argumentsq
* 
*/
char *argh_index(char **argh, const int index)
{
    if (index > 0 && index < sizeof(argh))
        return argh[index];
    return NULL;
}

int argh_size(char **argh, size_t *argh_len)
{
    return strlen(*argh) + 1;
}
#endif // ARGH_H
