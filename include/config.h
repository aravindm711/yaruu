#ifndef CONFIG_H
#define CONFIG_H

#ifdef __linux__

#define OS_CHECK return argp_parse(&argp, argc, argv, 0, 0, &arguments);
#define SPLIT_COMMAND "split"
#define SPLIT_DIR "/tmp/yaruu-split-dir/"
#define RECV_DIR "/tmp/yaruu-recv-dir/"
#define COMMAND "rsync"

#endif // Linux Conf.

#ifdef __APPLE__

#define OS_CHECK return argp_parse(&argp, argc, argv, 0, 0, &arguments);
#define SPLIT_COMMAND "gsplit"
#define SPLIT_DIR "/private/tmp/yaruu-split-dir/"
#define RECV_DIR "/private/tmp/yaruu-recv-dir/"
#define COMMAND "rsync"

#endif // Apple Conf.

// #if defined(__linux__) && defined(__APPLE__)

// #define OS_CHECK fprintf(stderr, "Incompatible OS for command.\nInstall linux or MacOS for proper functioning\n"); exit(0);

// #endif

#endif // CONFIG_H