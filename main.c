#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
//#include "get_next_line/get_next_line.c"

int main()
{
    int fd = open("test_lines.txt", 0);
    if (fd == -1)
        exit(-1);
    char *l = get_next_line(fd);
        for (; l; l = get_next_line(fd))
    {
        write(1,"[NL]",4);
        printf("%s", l);
        fflush(stdout);
        free((void*)l);
    }
    return 0;
}
