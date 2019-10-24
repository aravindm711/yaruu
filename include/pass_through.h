#ifndef PASS_THROUGH_H
#define PASS_THROUGH_H

#include <argh.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int run_pass_through(char ***arg, size_t *arg_len)
{
    int pipes[2];
    switch (fork())
    {
    case -1:
        perror("Bad fork (ps)");
        exit(1);
        break;
    case 0:
    {
        char command[256];
        snprintf(command, 256, "%s %s %s", (*arg)[0], (*arg)[1], (*arg)[2]);
        system(command);
        exit(1);
        break;
    }
    default:
        printf("yaruu exiting!");
        return 0;
    }
    return 1;
}
#endif // PASS_THROUGH_H