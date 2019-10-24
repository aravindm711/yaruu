#include <argp.h>
#include <stdbool.h> // defines _Bool as typedef alias bool
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <argh.h>
#include <argp_config.h>
#include <daemon.h>
#include <pass_through.h>
#include <yaruu.h>
#include <config.h>

/** 
 * 
 */
static error_t parse_options(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    switch (key)
    {
    case 'q':
    case 's':
        arguments->silent = 0;
        break;
    case 'v':
        arguments->verbose = 0;
        break;
    case 'd':
        arguments->mode = DAEMON_MODE;
        break;
    case 'p':
        arguments->mode = PASSTHROUGH_MODE;
        break;
    case ARGP_KEY_ARG:
    {
        arguments->argh = argh_add(arguments->argh, &arguments->argh_len, arg);
        break;
    }
    case ARGP_KEY_INIT:
        arguments->argh = 0;
        arguments->argh_len = 0;
        break;
    case ARGP_KEY_END: /* */
    {
        size_t count = arguments->argh_len;
        switch (arguments->mode)
        {
        case CLIENT_MODE:
            if (count > 3)
            {
                argp_failure(state, 1, 0, "too many arguments");
            }
            else if (count < 3)
            {
                argp_failure(state, 1, 0, "too few arguments");
            }
            run_client(arguments->argh, &arguments->argh_len);
            break;
        case DAEMON_MODE:
            run_daemon(&arguments->argh, &arguments->argh_len);
            break;
        case PASSTHROUGH_MODE:
            run_pass_through(&arguments->argh, &arguments->argh_len);
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

static struct argp argp = {
    options,       /* options struct defines all possible options. */
    parse_options, /* function pointer to option parser. */
    args_doc,      /* argument documentation used by argp. */
    doc,           /* general documentation used by argp. */
    0,             /* */
    0,             /* */
    0              /* */
};

struct arguments arguments = {
    1,           /* silent */
    1,           /* verbose */
    CLIENT_MODE, /* mode */
    NULL,        /* command's argument object */
    0            /* command's argument length*/
};

int main(int argc, char **argv)
{
    OS_CHECK
}