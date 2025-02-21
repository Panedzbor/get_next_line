#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test_lines.txt", 0);
    if (fd == -1)
        exit(-1);
    for (char *l = get_next_line(fd); l; l = get_next_line(fd))
    {
        printf("%s", l);
        fflush(stdout);
        free((void*)l);
    }
    return 0;
}