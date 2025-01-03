#include "stdio.h"
#include "stdlib.h"

char *_sio__strcpy(char *dest, const char *src)
{
    uint32_t i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void _sio__re_str(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }

    int start = 0;
    int end = len - 1;

    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Функция взята из https://github.com/0Nera/BMOSP
// Преобразование целого числа "i" в системе счисления "base" в строку "buf"
void _sio__inttoa(int32_t i, uint8_t base, char *buf)
{
    bool negative = false;

    // Проверяем, является ли число отрицательным
    if (i < 0)
    {
        negative = true;
        i *= -1; // Если да, то умножаем на -1, чтобы сделать его положительным
    }

    int32_t index = 0;
    // Деление с остатком для преобразования числа в нужную систему счисления
    do
    {
        int32_t remainder = i % base;
        // Преобразовываем остаток в символ и добавляем его в строку
        buf[index++] =
            (remainder > 9) ? (remainder - 10) + 'A' : remainder + '0'; // Если остаток > 9, добавляем заглавную букву А
        i /= base;
    } while (i > 0);

    // Если число было отрицательным, добавляем знак минуса в конец строки
    if (negative)
    {
        buf[index++] = '-';
    }

    // Добавляем нулевой символ в конец строки, чтобы завершить ее
    buf[index] = '\0';

    // Переворачиваем строку, чтобы цифры были в правильном порядке
    _sio__re_str(buf);
}

/*void _sio__int64toa(int64_t i, uint8_t base, char *buf)
{
    bool negative = false;

    // Проверяем, является ли число отрицательным
    if (i < 0)
    {
        negative = true;
        i *= -1; // Если да, то умножаем на -1, чтобы сделать его положительным
    }

    int64_t index = 0;
    // Деление с остатком для преобразования числа в нужную систему счисления
    do
    {
        int64_t remainder = i % base;
        // Преобразовываем остаток в символ и добавляем его в строку
        buf[index++] =
            (remainder > 9) ? (remainder - 10) + 'A' : remainder + '0'; // Если остаток > 9, добавляем заглавную букву А
        i /= base;
    } while (i > 0);

    // Если число было отрицательным, добавляем знак минуса в конец строки
    if (negative)
    {
        buf[index++] = '-';
    }

    // Добавляем нулевой символ в конец строки, чтобы завершить ее
    buf[index] = '\0';

    // Переворачиваем строку, чтобы цифры были в правильном порядке
    _sio__re_str(buf);
}*/

// Функция взята из https://github.com/0Nera/BMOSP
// Преобразование неотрицательного целого числа "i" в системе счисления "base" в строку "buf"
void _sio__uinttoa(uint32_t i, uint8_t base, char *buf)
{
    uint32_t index = 0;
    // Деление с остатком для преобразования числа в нужную систему счисления
    do
    {
        uint32_t remainder = i % base;
        // Преобразовываем остаток в символ и добавляем его в строку
        buf[index++] =
            (remainder > 9)
                ? (remainder - 10) + 'A'
                : remainder +
                      '0'; // Если остаток > 9, добавляем заглавную букву А
        i /= base;
    } while (i > 0);

    // Добавляем нулевой символ в конец строки, чтобы завершить ее
    buf[index] = '\0';

    // Переворачиваем строку, чтобы цифры были в правильном порядке
    _sio__re_str(buf);
}

/*void _sio__uint64toa(uint64_t i, uint8_t base, char *buf)
{
    uint64_t index = 0;
    // Деление с остатком для преобразования числа в нужную систему счисления
    do
    {
        uint64_t remainder = i % base;
        // Преобразовываем остаток в символ и добавляем его в строку
        buf[index++] =
            (remainder > 9)
                ? (remainder - 10) + 'A'
                : remainder +
                      '0'; // Если остаток > 9, добавляем заглавную букву А
        i /= base;
    } while (i > 0);

    // Добавляем нулевой символ в конец строки, чтобы завершить ее
    buf[index] = '\0';

    // Переворачиваем строку, чтобы цифры были в правильном порядке
    _sio__re_str(buf);
}*/

uint32_t _sio__strlen(const char *str) {
    uint32_t length = 0;
    while (*str)
    {
        length++;
        str++;
    }
    return length;
}

int fputs(char* __str, fd_t __stream) {
    return write(__stream, __str, _sio__strlen(__str));
}

void fputchar(char __char, fd_t __stream) {
    write(__stream, &__char, 1);
}

void putchar(char __char) {
    fputchar(__char, STDOUT_FILENO);
}

void vfprintf(fd_t __stream, const char* fmt, va_list argp) {
    char buffer[32];
    for (uint32_t i = 0; fmt[i] != '\0' ; i++)
    {
        if (fmt[i] == '%' && fmt[i+1] != '\0') {
            i++;
            switch (fmt[i])
            {
            case 's':
                char* str = va_arg(argp, char *);
                if(str != 0)
                    write(__stream, str, _sio__strlen(str));
                break;
            case 'c':
                fputchar((char)va_arg(argp, int), __stream);
                break;
            case 'i':
            case 'd':
                _sio__inttoa(va_arg(argp, int), 10, buffer);
                write(__stream, buffer, _sio__strlen(buffer));
                break;
            case 'u':
                _sio__uinttoa(va_arg(argp, int), 10, buffer);
                write(__stream, buffer, _sio__strlen(buffer));
                break;
            case 'p':
            case 'X':
            case 'x':
                _sio__uinttoa(va_arg(argp, int), 16, buffer);
                write(__stream, buffer, _sio__strlen(buffer));
                break;
            case 'l':
                switch (fmt[i+1]) {
                case 'l':
                    switch (fmt[i+2]) {
                    case 'u':
                        //_sio__uint64toa(va_arg(argp, uint64_t), 10, buffer);
                        write(__stream, buffer, _sio__strlen(buffer));
                        break;
                    case 'x':
                        //_sio__uint64toa(va_arg(argp, uint64_t), 16, buffer);
                        write(__stream, buffer, _sio__strlen(buffer));
                        break;
                    case 'd':
                    default:
                        //_sio__int64toa(va_arg(argp, uint64_t), 10, buffer);
                        write(__stream, buffer, _sio__strlen(buffer));
                        break;
                    }
                    i++;
                    break;
                default:
                    break;
                }
                i++;
                break;
            default:
                fputchar(fmt[i], __stream);
            }
        } else fputchar(fmt[i], __stream);
    }
}
void vprintf(const char* fmt, va_list argp) {
    vfprintf(STDOUT_FILENO, fmt, argp);
}

void fprintf(fd_t __stream, const char* __format, ...) {
    va_list args;
    va_start(args, __format);
    vfprintf(__stream, __format, args);
    va_end(args);
}

void printf(const char* __format, ...) {
    
    va_list args;
    va_start(args, __format);
    vfprintf(STDOUT_FILENO, __format, args);
    va_end(args);
}

void vsprintf(char* __s, const char* fmt, va_list argp) {
    char buffer[32];
    uint32_t di = 0;
    for (uint32_t i = 0; fmt[i] != '\0' ; i++)
    {
        if (fmt[i] == '%' && fmt[i+1] != '\0') {
            i++;
            switch (fmt[i])
            {
            case 's':
                char* str = va_arg(argp, char *);
                _sio__strcpy(&__s[di], str);
                di += _sio__strlen(buffer);
                break;
            case 'c':
                __s[di] = (char)va_arg(argp, int);
                di++;
                break;
            case 'i':
            case 'd':
            
                _sio__inttoa(va_arg(argp, int), 10, buffer);
                _sio__strcpy(&__s[di], buffer);
                di += _sio__strlen(buffer);
                break;
            case 'u':
                _sio__uinttoa(va_arg(argp, int), 10, buffer);
                _sio__strcpy(&__s[di], buffer);
                di += _sio__strlen(buffer);
                break;
            case 'p':
            case 'X':
            case 'x':
                _sio__strcpy(&__s[di], buffer);
                di += _sio__strlen(buffer);
                break;
            case 'l':
                switch (fmt[i+1]) {
                case 'l':
                    switch (fmt[i+2]) {
                    case 'u':
                        //_sio__uint64toa(va_arg(argp, uint64_t), 10, buffer);
                        _sio__strcpy(&__s[di], buffer);
                        di += _sio__strlen(buffer);
                        break;
                    case 'x':
                        //_sio__uint64toa(va_arg(argp, uint64_t), 16, buffer);
                        _sio__strcpy(&__s[di], buffer);
                        di += _sio__strlen(buffer);
                        break;
                    case 'd':
                    default:
                        //_sio__int64toa(va_arg(argp, uint64_t), 10, buffer);
                        _sio__strcpy(&__s[di], buffer);
                        di += _sio__strlen(buffer);
                        break;
                    }
                    i++;
                    break;
                default:
                    break;
                }
                i++;
                break;
            default:
                __s[di] = fmt[i];
                
            }
        } else {
            __s[di] = fmt[i];
            di++;
        } 
    }
}

void sprintf(char* __s, const char* __format, ...) {
    va_list args;
    va_start(args, __format);
    vsprintf(__s, __format, args);
    va_end(args);
}

int getchar(void) {
    char ch;
    for(;;) {
        read(STDIN_FILENO, &ch, 1);
        if(ch != 0) break;
    }
    return ch;
}

int fgetc(fd_t __stream) {
    char ch;
    for(;;) {
        read(__stream, &ch, 1);
        if(ch != 0) break;
    }
    return ch;
}

int getc(fd_t __stream) {
    return fgetc(__stream);
}

char* __fgets_stdin(char* __buff, size_t __n) {
    size_t i;
    for (i = 0; i < __n; i++) {
        __buff[i] = fgetc(STDIN_FILENO);
        putchar(__buff[i]);
        if(__buff[i] == '\n')
            break;
    }
    __buff[i] = '\0';
    return __buff;
}

char* fgets(char* __buff, size_t __n, fd_t __stream) {
    if(__stream == STDIN_FILENO)
        return __fgets_stdin(__buff, __n);
    size_t i;
    for (i = 0; i < __n; i++) {
        read(__stream, &__buff[i], 1);
        if( __buff[i] == '\n' || __buff[i] == '\0')
            break;
    }
    __buff[i] = '\0';
    return __buff;
}

void __doscnf(const char* fmt, va_list argp, fd_t __stream) {
    char buffer[32];
    for (uint32_t i = 0; fmt[i] != '\0' ; i++)
    {
        if (fmt[i] == '%' && fmt[i+1] != '\0') {
            i++;
            switch (fmt[i])
            {
            case 's':
                char* str = va_arg(argp, char *);
                fgets(str, UINT16_MAX, __stream);
                
                break;
            case 'c':
                *(va_arg(argp, char*)) = fgetc(__stream);
                break;
            case 'i':
            case 'd':
                fgets(buffer, 32, __stream);
                *(va_arg(argp, int*)) = atoi(buffer);
                break;
            case 'u':
                fgets(buffer, 32, __stream);
                *(va_arg(argp, unsigned int*)) = atoi(buffer);
                break;
            case 'p':
            case 'X':
            case 'x':
                fgets(buffer, 32, __stream);
                *(va_arg(argp, int*)) = atoi(buffer);
                break;
            case 'l':
                switch (fmt[i+1]) {
                case 'l':
                    switch (fmt[i+2]) {
                    case 'u':
                        fgets(buffer, 32, __stream);
                        *(va_arg(argp, long long*)) = atoll(buffer);
                        break;
                    case 'x':
                        fgets(buffer, 32, __stream);
                        *(va_arg(argp, long long*)) = atoll(buffer);
                        break;
                    case 'd':
                    default:
                        fgets(buffer, 32, __stream);
                        *(va_arg(argp, long long*)) = atoll(buffer);
                        break;
                    }
                    i++;
                    break;
                default:
                    break;
                }
                i++;
                break;
            default:
                
            }
        } else {

        }
    }
}

int fscanf(fd_t __stream, const char* __format, ...) {
    va_list args;
    va_start(args, __format);
    __doscnf(__format, args, __stream);
    va_end(args);
}

int scanf(const char* __format, ...) {
    va_list args;
    va_start(args, __format);
    __doscnf(__format, args, STDIN_FILENO);
    va_end(args);
}

void perror(const char* __s) {
    fputs(__s, STDERR_FILENO);
}

