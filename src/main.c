#include <stdbool.h> // defines _Bool as typedef alias bool
#include <unistd.h>
#include <argp.h>
#include <stdio.h>
/*
 * Set argp globals 
 */
// Program version
const char *argp_program_version = "yaruu, v0.0.0";
// Program bug address
const char *argp_program_bug_address = "https://github.com/aravindm711/yaruu/issues";
// Program doc.
static char doc[] = "yaruu is a minimal and lightweight rsync wrapper that keeps it simple.\
\vAuthored by:\nAakash Hemadri(https://github.com/aakashhemadri)\n\
& Aravind Murali(https://github.com/aravindm711)";
static char args_doc[] = "[FILENAME]...";
static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output."},
    {"quiet", 'q', 0, 0, "Don't produce any output."},
    {"silent", 's', 0, OPTION_ALIAS},
    {"daemon", 'd', 0, 0, "Runs yaruu as a daemon."},
    {"pass-through", 'p', "RSYNC_ARGS", 0, "Passes through all options directly to the rsync daemon.", 0},
    {0}};
struct arguments
{
  bool silent, verbose;
  enum
  {
    DAEMON_MODE,
    PASSTHROUGH_MODE,
    CLIENT_MODE
  } mode;
  char *string;
};

static error_t parse_options(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;
  switch (key)
  {
  case 'q':
  case 's':
    arguments->silent = true;
    break;
  case 'v':
    arguments->verbose = true;
    break;
  case 'd':
    arguments->mode = DAEMON_MODE;
    break;
  case 'p':
    arguments->mode = PASSTHROUGH_MODE;
    break;
  case ARGP_KEY_ARG:
    arguments->string = arg;
    state->next = state->argc + 1;
    break;
  case ARGP_KEY_NO_ARGS:
    argp_usage(state);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
}
static struct argp argp = {options, parse_options, args_doc, doc, 0, 0, 0};

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
    break;
  case PASSTHROUGH_MODE:
    printf("Starting rsync through passthrough...\n");
    break;
  }
  return 0;
}