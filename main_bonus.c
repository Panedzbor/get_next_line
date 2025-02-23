#include "get_next_line/get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd1 = open("test_lines.txt", 0);
    int fd2 = open("test_lines2.txt", 0);
    int fd3 = open("test_lines3.txt", 0);
    int fds[] = {fd1, fd2, fd3};
    if (fd1 == -1 || fd2 == -1 || fd3 == -1)
        exit(-1);
    char *l = NULL;
    for (int i = 0, index = 0, c = 0; c < 3; i++)
    {
        index = i % 3;
        l = get_next_line(fds[index]);
        if (l)
        {
            write(1,"!",1);
            printf("%s", l);
            fflush(stdout);
            free((void*)l);
        }
        else
            c++;
    }
    return 0;
}