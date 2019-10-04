#include <stdio.h>

int main() {
    printf("yeah, mate!\n");

int main(int argc, char **argv)
{
  struct arguments arguments;
  arguments.mode = CLIENT_MODE;
  arguments.silent = false;
  arguments.verbose = false;
  arguments.string = "[FILENAME]...";
  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  switch (arguments.mode)
  {
  case CLIENT_MODE:
    printf("Starting rsync in client mode...\n");
    printf("ARGS %s\n", arguments.string);
    break;
  case DAEMON_MODE:
    printf("Starting the rsync daemon...\n");
    execlp("rsync", "--help");
    break;
  case PASSTHROUGH_MODE:
    printf("Starting rsync through passthrough...\n");
    break;
  }
  return 0;
}