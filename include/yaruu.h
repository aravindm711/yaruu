#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <config.h>

#ifndef YARUU_H
#define YARUU_H

/** yaruu_mode enum type
 * 
 */
typedef enum yaruu_mode
{
    SRC_DEST,     // SRC [SRC]... DEST
    SRC_HOST,     // SRC [SRC]... [USER@]HOST:DEST
    SRC_DAEMON,   // SRC [SRC]... [USER@]HOST::DEST
    SRC_PROTOCOL, // SRC [SRC]... rsync://[USER@]HOST[:PORT]/DEST
    HOST_DEST,    // [USER@]HOST:SRC [DEST]
    DAEMON_DEST,  // [USER@]HOST::SRC [DEST]
    PROTOCOL_DEST // rsync://[USER@]HOST[:PORT]/SRC [DEST]
} mode;

void split_file(char **);
mode validate(char **);
void create_dir();
void remove_dir();

int run_client(char **arg, size_t *arg_len)
{
    switch (validate(arg))
    {
    case SRC_DEST:
    {
        split_file(arg);
        break;
    }
    case SRC_HOST:
    {
        break;
    }
    case SRC_DAEMON:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    return 0;
}

/** Validating arguments.
 * Parses the arguments to infer the kind of file transfer.
 * @param arg: (char **)
 */
mode validate(char **arg)
{
    return SRC_DEST;
}

/** Calculates file size from path.
 * Returns the size of the file given in bytes
 * 
 * @param: const char* (File path)
 * @return: off_t (Size of file in bytes.)
*/
off_t file_size(const char *file_path)
{
    struct stat st;

    if (stat(file_path, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s\n", file_path);

    return -1;
}

void remove_dir()
{
    struct stat st = {0};
    if (stat(SPLIT_DIR, &st) == 0)
    {
        char command[40];
        sprintf(command, "rm -rf %s", SPLIT_DIR);
        system(command);
    }
}

void create_dir()
{
    struct stat st = {0};
    if (stat(SPLIT_DIR, &st) == -1)
    {
        mkdir(SPLIT_DIR, 0777);
    }
}

void split_file(char **arg)
{
    create_dir();

    char final_command[100];
    snprintf(final_command, 100, "%s %s %ssplitfile_", SPLIT_COMMAND, arg[1], SPLIT_DIR);
    system(final_command);
    printf("running: %s\n", final_command);

    remove_dir();
}

bool send_files()
{
    return true;
}
#endif // YARUU_H