#include <stdbool.h> // defines _Bool as typedef alias bool
#include <unistd.h>
#include <argp.h>
#include <stdio.h>
/*
 * Set argp globals 
 */
const char *argp_program_version = "yaruu, v0.0.0";
const char *argp_program_bug_address = "https://github.com/aravindm711/yaruu/issues";
static char doc[] = "yaruu is a minimal and lightweight rsync wrapper that keeps it simple.";
static char args_doc[] = "[FILENAME]...";
static struct argp_option options[] = {
    {"daemon", 'd', "DAEMON_ARGS", 0, "Runs yaruu as a daemon.", 0},
    {"pass-through", 'p', "RSYNC_ARGS", 0, "Passes through all options directly to the rsync daemon.", 0},
    {0}};
struct arguments
{
  enum
  {
    DAEMON_MODE,
    PASSTHROUGH_MODE,
    CLIENT_MODE
  } mode;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;
  switch (key)
  {
  case 'd':
    arguments->mode = DAEMON_MODE;
    break;
  case 'p':
    arguments->mode = PASSTHROUGH_MODE;
    break;
  case ARGP_KEY_ARG:
    return 0;
  default:
    return ARGP_ERR_UNKNOWN;
  }
}
static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

int main(int argc, char **argv)
{
  struct arguments arguments;
  arguments.mode = DAEMON_MODE;
  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  printf("Hello!");

  return 0;
}