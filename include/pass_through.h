#ifndef PASS_THROUGH_H
#define PASS_THROUGH_H

#include <stdlib.h>
#include <stdio.h>
#include <argh.h>
#include <unistd.h>

int run_pass_through(char **arg, size_t *arg_len)
{
  char **result = (char **)malloc(*arg_len);
  result = argh_extract(arg, arg_len, result);
  switch (fork())
  {
  case -1:
    perror("Bad fork (ps)");
    exit(1);
    break;
  case 0:
    execvp("rsync", result);
    // printf("%s %s", result[0], result[1]);
    break;
  default:
    exit(1);
    return 0;
  }
  return 1;
}
#endif // PASS_THROUGH_H