#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#ifndef YARUU_H
#define YARUU_H

void split_file(char**);
void create_dir(char*);
void remove_dir(char*);

int run_client(char **arg, size_t *arg_len)
{
    split_file(arg);

    return 0;
}

/*
 * Function: file_size
 * 
 * Returns the size of the file given in bytes
 * 
 * file_path: path to the file ( char* )
 * 
 * returns: size of the file given in bytes ( off_t )
 *          returns -1 on error ( if file is invalid )
*/
off_t file_size(const char* file_path) {
    struct stat st;

    if (stat(file_path, &st) == 0)
        return st.st_size;

    // fprintf(stderr, "Cannot determine size of %s: %s\n",
    //         file_path, strerror(errno));

    return -1;
}

void remove_dir(char* dir) {
    struct stat st = {0};
    if (stat(dir, &st) == 0) {
        char command[40];
        sprintf(command, "rm -rf %s", dir);
        system(command);
    }
}

void create_dir(char* dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0777);
    }
}

void split_file(char** arg) {
    char* yaruu_split_dir;
    char* split_command;
    char final_command[100];
    char os[10];

    FILE* os_info;
    os_info = popen("/usr/bin/uname", "r");
    if (os_info != NULL) {
        if (!feof(os_info)) {
            fgets(os, 10, os_info);
        }
        pclose(os_info);
    }

    if (strncmp(os, "Darwin", 6) == 0) {
        split_command = (char *)"gsplit";
        yaruu_split_dir = (char *)"/private/tmp/yaruu-split-dir/";
    } else if (strncmp(os, "Linux", 5) == 0) {
        split_command = (char *)"split";
        yaruu_split_dir = (char *)"/tmp/yaruu-split-dir/";
    } else {
        printf("Not a Darwin/Linux system. Get one, to use this command.\n");
        exit(0);
    }

    create_dir(yaruu_split_dir);
    snprintf(final_command, 100, "%s %s %ssplitfile_", split_command, arg[0], yaruu_split_dir);
    system(final_command);
    printf("running: %s\n", final_command);
    remove_dir(yaruu_split_dir);
}

#endif // YARUU_H