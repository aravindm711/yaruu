#ifndef DAEMON_H
#define DAEMON_H

int run_daemon(char **arg, size_t *arg_len)
{
    printf("%s", *arg);
    return 0;
}

#endif // DAEMON_Hq