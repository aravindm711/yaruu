# yaruu - yet another rsync wrapper

yaruu is a lightweight rsync wrapper.

- yaruu's primary goal is to try and optimize file transfers across systems and networks.

## Features

- Substantial performance boosts.
  - [ ] Source is a file.
  - [ ] Source is a directory.
- POSIX compliance.
- argument parsing using argp.h
- Cross-Platform (Darwin & Linux)
- Weight based algorithm for file split.
  - Algorithm must poll network and figure best split to size ratio.
- glob rsync commands.

## Dependencies

- rsync
- gnu-coreutils
  - split
  - cat
- gnu-lib
  - parallel
- argp
- shc

## Contributers

- [Aakash Hemadri](https://github.com/aakashhemadri)
- [Aravind Murali](https://github.com/aravindm711)

## License

[GNU Lesser Public License](License.md)
