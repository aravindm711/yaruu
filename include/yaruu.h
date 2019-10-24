#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

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

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            file_path, strerror(errno));

    return -1;
}

void split_file(char **arg)
{
    char buffer[10];
    FILE *os_info;
    os_info = popen("/usr/bin/uname", "r");
    if (os_info != NULL)
    {
        if (!feof(os_info))
        {
            fgets(buffer, 10, os_info);
        }
        pclose(os_info);
    }

    char *os = buffer;
    if (strncmp(os, "Darwin", 6) == 0)
    {
        printf("yep");
    }
    else if (strncmp(buffer, "Linux", 5) == 0)
    {
        struct stat st = {0};
        if (stat("/tmp/yaruu-split-dir/", &st) == -1)
        {
            mkdir("/tmp/yaruu-split-dir/", 0777);
        }

        char *split_command = (char *)"split ";
        const char *split_dir = " /var/yaruu-split-dir/split_file_";
        split_command = (char *)realloc(split_command, sizeof(split_command) + sizeof(arg[0]) + sizeof(split_dir));
        split_command = strcat(split_command, arg[0]);
        split_command = strcat(split_command, split_dir);
        system(split_command);
    }
}

bool send_files()
{

    return true;
}
#endif // YARUU_H