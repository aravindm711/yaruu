#include <argp.h>

#ifndef ARGP_CONFIG_H
#define ARGP_CONFIG_H

/*
 * Set argp globals 
 */

// Program version
const char *argp_program_version = "yaruu-v0.0.0, yaruu is a minimal and lightweight rsync wrapper.";

// Program bug address
const char *argp_program_bug_address = "https://github.com/aravindm711/yaruu/issues";

// Program doc.
static char doc[] = "yaruu is a minimal and lightweight rsync wrapper that keeps it simple.\
\vAuthored by:\nAakash Hemadri(https://github.com/aakashhemadri)\n\
& Aravind Murali(https://github.com/aravindm711)";

static char args_doc[] = "SRC [SRC]... DEST\nSRC [SRC]... [USER@]HOST:DEST\nSRC [SRC]... [USER@]HOST::DEST\nSRC [SRC]... rsync://[USER@]HOST[:PORT]/DEST\n[USER@]HOST:SRC [DEST]\n[USER@]HOST::SRC [DEST]\nrsync://[USER@]HOST[:PORT]/SRC [DEST]";

static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output."},
    {"quiet", 'q', 0, 0, "Don't produce any output."},
    {"silent", 's', 0, OPTION_ALIAS},
    {"daemon", 'd', "DAEMON_ARGS", OPTION_ARG_OPTIONAL, "Runs yaruu as a daemon."},
    {"pass-through", 'p', "RSYNC_ARGS", OPTION_ARG_OPTIONAL, "Passes through all options directly to the rsync daemon.", 0},
    {0}};

struct arguments /* argument struct manipulated during recursive parse */
{
    int silent, verbose;
    enum
    {
        DAEMON_MODE,
        PASSTHROUGH_MODE,
        CLIENT_MODE
    } mode;
    char **argh;
    size_t argh_len;
};

#endif //ARGP_CONFIG_H