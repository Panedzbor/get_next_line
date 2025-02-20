#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>



char *concat_left(ssize_t len, char *str, t_st *st);
char    *erase_left(t_st *st);
char *overwrite_left(ssize_t len, char *str, ssize_t i, t_st *st);
char *compose_newl(char *str, ssize_t last_char, t_st *st);
char *search_newl(char *str, ssize_t len, t_st *st, bool *buf);
ssize_t count_size(char *str);
void    init_struct(t_st *st, int fd);
char    *get_next_line(int fd);

int main()
{
    int fd = open("../test_lines.txt", 0);
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

char    *get_next_line(int fd)
{
    ssize_t     len;
    static t_st st;
    bool        buf;

    if (!st.left)
        init_struct(&st, fd);
    buf = false;
    if (!st.left || st.check != 0)
    {
        len = read(fd, st.buffer, BUFFER_SIZE);
        if (len <= 0 && !st.left)
            return (NULL);
        if (len < BUFFER_SIZE)
            return (compose_newl(st.buffer, len - 1, &st));
        st.buffer[len] = '\0';
        buf = true;
    }
    else
        len = count_size(st.left);
    if (buf)
        return (search_newl(st.buffer, len, &st, &buf));
    return (search_newl(st.left, len, &st, &buf));
}

void    init_struct(t_st *st, int fd)
{
    st->left = NULL;
    st->check = 0;
    st->fd = fd;
}

ssize_t count_size(char *str)
{
    ssize_t i;

    if (!str)
        return (0);
    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char *search_newl(char *str, ssize_t len, t_st *st, bool *buf)
{
    ssize_t  i;
    char    *next_line;

    i = 0;
    while (i < len)
    {
        if (str[i] == '\n')
        {
            if (!*buf)
                st->check = 1;
            next_line = compose_newl(str, i, st);
            st->left = overwrite_left(len, str, i, st);
            return (next_line);
        }
        i++;
    }
    if (!*buf)
        st->check = -1;
    else
        st->left = concat_left(len, str, st);
    next_line = get_next_line(st->fd);
    return (next_line);
}

char *compose_newl(char *str, ssize_t last_char, t_st *st)
{
    char    *next_line;
    ssize_t i;
    ssize_t leftlen;
    
    leftlen = 0;
    if (st->left && st->check == -1)
        leftlen = count_size(st->left);
    next_line = (char *)malloc(leftlen + last_char + 2);
    if (!next_line)
        return (NULL);
    i = 0;
    while (i < leftlen)
    {
        next_line[i] = st->left[i];
        i++;
    }
    if (leftlen > 0)
        st->left = erase_left(st);
    while (i - leftlen <= last_char)
    {
        next_line[i] = str[i - leftlen];
        i++;
    }
    next_line[i] = '\0';
    return (next_line);
}

char *overwrite_left(ssize_t len, char *str, ssize_t i, t_st *st)
{
    char    *new_left;
    ssize_t y;
    
    if (len - i <= 1)
        return (erase_left(st));
    new_left = (char *)malloc(len - i);
    if (!new_left)
        return (NULL);
    i++;
    y = 0;
    while (i < len + 1)
        new_left[y++] = str[i++];
    erase_left(st);
    return (new_left);
}


char    *erase_left(t_st *st)
{
    if (st->left)
        free((void *)st->left);
    st->check = 0;
    return (NULL);   
}

char *concat_left(ssize_t len, char *str, t_st *st)
{
    char    *new_left;
    ssize_t     i;
    ssize_t     j;

    len += count_size(st->left) + 1;
    new_left = (char *)malloc(len);
    if (!new_left)
        return (NULL);
    i = 0;
    if (st->left)
    {
        while (st->left[i] != '\0')
        {
            new_left[i] = st->left[i];
            i++;
        }
    }
    j = 0;
    while (i < len)
        new_left[i++] = str[j++];
    erase_left(st);
    st->check = -1;
    return (new_left);
}
