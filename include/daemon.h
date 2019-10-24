#ifndef DAEMON_H
#define DAEMON_H

int run_daemon(char ***arg, size_t *arg_len)
{
    for (int i = 0; i < 2; i++)
    {
        printf("%s", (*arg)[i]);
    }

    return 0;
}

#endif // DAEMON_Hq