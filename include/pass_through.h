#ifndef PASS_THROUGH_H
#define PASS_THROUGH_H

#include <stdlib.h>
#include <stdio.h>
#include <argh.h>
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
    // for(int i = 0 ; i<3 ; i++){ 
    //   printf("%s",(*arg)[i]);
    //   }
    execvp("rsync", *arg);
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