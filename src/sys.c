#include "sys.h"

void exit(int code) {
    asm volatile("int $0x80" : : "a"(1), "b"(code));
    for(;;);
}

pid_t fork(void) {
    return 0;
}

size_t read(fd_t __fd, char *__buf, size_t __nbytes) {
    size_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(3), "b"(__fd), "c"(__buf), "d"(__nbytes));
    return ret;
}

size_t write(fd_t __fd, const char *__buf, size_t __n) {
    size_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(4), "b"(__fd), "c"(__buf), "d"(__n));
    return ret;
}

fd_t open(const char* __path, int __flags) {
    fd_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(5), "b"(__path), "c"(__flags));
    return ret;
}

int close(fd_t __fd) {
    fd_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(6), "b"(__fd));
    return ret;
}

off_t lseek(fd_t __fd, off_t __offset, int __whence) {
    fd_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(19), "b"(__fd), "c"(__offset), "d"(__whence));
    return ret;
}

int chdir(const char* path) {
    pid_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(12), "b"(path));
    return ret;
}

int pipe(fd_t pipefd[2]) {
    pid_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(0x2a), "b"(pipefd));
    return ret;
}

int ioctl(fd_t fd, unsigned long op, void* arg) {
    pid_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(0x36), "b"(fd), "c"(op), "d"(arg));
    return ret;
}
