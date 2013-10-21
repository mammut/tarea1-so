#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "../include/imprimidor.h"
 

int imprimidor(FILE *salida, const char *format, ...) {
    int status;
    va_list args;
    char buffer[1024];

    va_start(args, format);
    status = vsprintf(buffer, format, args);
    va_end(args);
    
    write(fileno(salida), buffer, strlen(buffer));

    return status;
}