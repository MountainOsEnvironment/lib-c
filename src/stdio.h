#ifndef STDIO_H_
#define STDIO_H_

#include <stdint.h>
#include <stdarg.h>
#include "sys.h"

typedef int bool;
#define true 1
#define false 0

#define O_ACCMODE	   0003
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#ifndef O_CREAT
# define O_CREAT	   0100	/* Not fcntl.  */
#endif
#ifndef O_EXCL
# define O_EXCL		   0200	/* Not fcntl.  */
#endif
#ifndef O_NOCTTY
# define O_NOCTTY	   0400	/* Not fcntl.  */
#endif
#ifndef O_TRUNC
# define O_TRUNC	  01000	/* Not fcntl.  */
#endif
#ifndef O_APPEND
# define O_APPEND	  02000
#endif
#ifndef O_NONBLOCK
# define O_NONBLOCK	  04000
#endif
#ifndef O_NDELAY
# define O_NDELAY	O_NONBLOCK
#endif
#ifndef O_SYNC
# define O_SYNC	       04010000
#endif
#define O_FSYNC		O_SYNC
#ifndef O_ASYNC
# define O_ASYNC	 020000
#endif
#ifndef __O_LARGEFILE
# define __O_LARGEFILE	0100000
#endif

#ifndef __O_DIRECTORY
# define __O_DIRECTORY	0200000
#endif
#ifndef __O_NOFOLLOW
# define __O_NOFOLLOW	0400000
#endif
#ifndef __O_CLOEXEC
# define __O_CLOEXEC   02000000
#endif
#ifndef __O_DIRECT
# define __O_DIRECT	 040000
#endif
#ifndef __O_NOATIME
# define __O_NOATIME   01000000
#endif
#ifndef __O_PATH
# define __O_PATH     010000000
#endif
#ifndef __O_DSYNC
# define __O_DSYNC	 010000
#endif
#ifndef __O_TMPFILE
# define __O_TMPFILE   (020000000 | __O_DIRECTORY)
#endif

/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

enum {
    stdin,
    stdout,
    stderr,
};

int fputs(char* __str, fd_t __stream);

void fputchar(char __char, fd_t __stream);

void putchar(char __char);

void vfprintf(fd_t __stream, const char* __format, va_list argp);

void vprintf(const char* __format, va_list argp);

void fprintf(fd_t __stream, const char* __format, ...);

void printf(const char* __format, ...);

void vsprintf(char* __s, const char* __format, va_list argp);

void sprintf(char* __s, const char* __format, ...);

int getchar(void);

int fgetc(fd_t __stream);

int getc(fd_t __stream);

char* fgets(char* __buff, size_t __n, fd_t __stream);

int fscanf(fd_t __stream, const char* __format, ...);

int scanf(const char* __format, ...);

void perror(const char* __s);

#endif //STDIO_H_