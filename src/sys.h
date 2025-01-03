#ifndef MOSSYS_H_
#define MOSSYS_H_

#define EXIT_SUCCESS 0

typedef          int fd_t;
typedef unsigned int pid_t;
typedef unsigned int mode_t;

typedef unsigned int size_t;
typedef unsigned int off_t;

#include "sys.h"

void exit(int code);

pid_t fork(void);

size_t read(fd_t __fd, char *__buf, size_t __nbytes);

size_t write(fd_t __fd, const char *__buf, size_t __n);

fd_t open(const char* __path, int __flags);

int close(fd_t __fd);

off_t lseek(fd_t __fd, off_t __offset, int __whence);

int chdir(const char* path);

int pipe(fd_t pipefd[2]);

int ioctl(fd_t fd, unsigned long op, void *arg);

#endif //MOSSYS_H_