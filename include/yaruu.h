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

/** Helper functions.
 * 
 */
int count_dir(int);
int check_dir(int);
int create_dir(int);
int remove_dir(int);
char **list_dir(int, int, char **);

/** Core Functionality.
 * 
 */
mode validate(char **);
int cat_file(char **, char **);
int split_file(char **);
int send_files(char **, char **, int);

int run_client(char **arg, size_t *arg_len)
{
    switch (validate(arg))
    {
    case SRC_DEST:
    {
        if (split_file(arg))
        {
            return 1;
        }
        char** files = malloc(sizeof(char *) * count_dir(1));
        cat_file(list_dir(count_dir(1), 1, files), arg);
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
    case SRC_PROTOCOL:
    {
        break;
    }
    case HOST_DEST:
    {
        break;
    }
    case DAEMON_DEST:
    {
        break;
    }
    case PROTOCOL_DEST:
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

/** Removes directory.
 * @return int (failure/success)
 */
int remove_dir(int sorc)
{
    const char *dir = (sorc == 0) ? SPLIT_DIR : RECV_DIR;
    struct stat st = {0};
    if (stat(dir, &st) == 0)
    {
        char command[40];
        sprintf(command, "rm -rf %s", dir);
        system(command);
        return 0;
    }

    return 1;
}

/** Directory Creation.
 * @return int (failure/success)
 */
int create_dir(int sorc)
{
    const char *dir = (sorc == 0) ? SPLIT_DIR : RECV_DIR;
    struct stat st = {0};
    if (stat(dir, &st) == -1)
    {
        mkdir(dir, 0777);
    }

    if (stat(dir, &st) == -1)
    {
        return 1;
    }

    return 0;
}

/** Counts number of files in the RECV_DIR
 *  @return int (count)
 */
int count_dir(int sorc)
{
    const char *dir = (sorc == 0) ? SPLIT_DIR : RECV_DIR;
    if (check_dir(sorc))
    {
        char command[45];
        snprintf(command, 45, "ls %s | wc -l", dir);
        FILE *num_of_files = popen(command, "r");
        int count = 0;
        if (num_of_files)
        {
            fscanf(num_of_files, "%d", &count);
        }

        return count;
    }

    return 0;
}

/** List of files in the directory RECV_DIR
 *  @return char** (files)
 */
char **list_dir(int count, int sorc, char **files)
{
    const char *directory = (sorc == 0) ? SPLIT_DIR : RECV_DIR;
    if (check_dir(sorc))
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(directory);
        if (d)
        {
            for (int i = -2; i < count; i++)
            {
                dir = readdir(d);
                if (i >= 0)
                {
                    files[i] = malloc(20);
                    strcpy(files[i], dir->d_name);
                }
            }
            closedir(d);

            return files;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

/** Checks validity of RECV_DIR
 *  @return int (success/failure)
 */
int check_dir(int sorc)
{
    const char *dir = (sorc == 0) ? SPLIT_DIR : RECV_DIR;
    struct stat st = {0};
    if (stat(dir, &st) == 0)
    {
        return 1;
    }

    return 0;
}

/** Concatenate all split files from RECV_DIR
 *  @return int (success/failure)
 */
int cat_file(char **files, char **arg)
{
    create_dir(1);

    int count = count_dir(1);
    files = list_dir(count, 1, files);

    char cat_command[1024], absolute_path_to_file[256], recv_file_path[256];
    snprintf(cat_command, 5, "cat ");
    for (int i = 0; i < count; i++)
    {
        snprintf(absolute_path_to_file, 256, "%s%s ", RECV_DIR, files[i]);
        strcat(cat_command, absolute_path_to_file);
    }
    snprintf(recv_file_path, 256, " >> %s/recv_file", arg[2]);
    strcat(cat_command, recv_file_path);
    printf("%s\n", cat_command);
    printf("merging files...\n");
    system(cat_command);
    printf("received file merged and created\n");

    remove_dir(1);

    return 0;
}

/** Splitting file.
 * Splits file into appropriate sizes.
 */
int split_file(char **arg)
{
    if (create_dir(0))
    {
        return 1;
    }

    char final_command[256];
    snprintf(final_command, 256, "%s -n 4 %s %ssplitfile_", SPLIT_COMMAND, arg[1], SPLIT_DIR);
    system(final_command);
    printf("running: %s\n", final_command); /* Requires to be put in appropriate verbose print statements*/
    printf("splitting files...\n");

    char **files = malloc(sizeof(char *) * count_dir(0));
    if (send_files(arg, list_dir(count_dir(0), 0, files), count_dir(0)))
    {
        return 1;
    }

    if (remove_dir(0))
    {
        return 1;
    }

    return 0;
}

int split_algorithm(char **arg)
{
    return file_size(arg[1])/4;
}

int send_files(char **arg, char **files, int no_of_files)
{
    if (no_of_files)
    {
        printf("sending files to %s\n", arg[2]);
        for (int i = 0; i < no_of_files; i++)
        {
            char command[256];
            /* Required to add support for globbed arguments */

            snprintf(command, 256, "%s %s%s %s", COMMAND, SPLIT_DIR, files[i], RECV_DIR);
            system(command);
            printf("sending %s\n", files[i]);
        }

        return 0;
    }

    return 1;
}

#endif // YARUU_H