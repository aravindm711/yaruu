#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // defines _Bool as typedef alias bool
#include <unistd.h>
#include <argp.h>

#include <yaruu.h>
#include <argp_config.h>
#include <argh.h>
#include <daemon.h>

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
    argh_add(&arguments->argh, &arguments->argh_len, arg);
    break;
  case ARGP_KEY_INIT:
    arguments->argh = 0;
    arguments->argh_len = 0;
    break;
  case ARGP_KEY_END:
  {
    size_t count = arguments->argh_len;
    switch (arguments->mode)
    {
    case CLIENT_MODE:
      if (count > 2)
      {
        argp_failure(state, 1, 0, "too many arguments");
      }
      else if (count < 2)
      {
        argp_failure(state, 1, 0, "too few arguments");
      }
      run_client(arguments->argh, arguments->argh_len);
      break;
    case DAEMON_MODE:
      run_daemon(arguments->argh, arguments->argh_len);
      break;
    case PASSTHROUGH_MODE:
      // run_pass_through(arguments->argh, arguments->argh_len);
      break;
    }
  }
  break;
  case ARGP_KEY_NO_ARGS:
    argp_usage(state);
    break;
  default:
    break;
  }
  return 0;
}
static struct argp argp = {options, parse_options, args_doc, doc, 0, 0, 0};
struct arguments arguments = {false, false, CLIENT_MODE, 0, 0};

int main(int argc, char **argv)
{
  return argp_parse(&argp, argc, argv, 0, 0, &arguments);
}