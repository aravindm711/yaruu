#ifndef PASS_THROUGH_H
#define PASS_THROUGH_H

#include <argh.h>
#include <unistd.h>

int run_pass_through(char **arg, size_t *arg_len)
{
  char **result = NULL;
  result = argh_extract(arg, arg_len, result);
  execvp("rsync", result);
  return 0;
}
#endif // PASS_THROUGH_H