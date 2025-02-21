/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/18 14:23:51 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *search_newl(char *str, ssize_t len, t_st *st, bool *buf);
static char *compose_newl(char *str, ssize_t last_char, t_st *st);
static char *overwrite_left(ssize_t len, char *str, ssize_t i, t_st *st);
static char *concat_left(ssize_t len, char *str, t_st *st);

char    *get_next_line(int fd)
{
    ssize_t     len;
    static t_st *st;
    int         index;
    bool        buf;

    index = check_fd(fd, st);
    if (!st[index].left)
        init_struct(&st[index], fd);
    buf = false;
    if (!st[index].left || st[index].check != 0)
    {
        len = read(fd, st[index].buffer, BUFFER_SIZE);
        if (len <= 0 && !st[index].left)
            return (NULL);
        if (len < BUFFER_SIZE)
            return (compose_newl(st[index].buffer, len - 1, &st[index]));
        st[index].buffer[len] = '\0';
        buf = true;
    }
    else
        len = count_size(st[index].left);
    if (buf)
        return (search_newl(st[index].buffer, len, &st[index], &buf));
    return (search_newl(st[index].left, len, &st[index], &buf));
}

char    *search_newl(char *str, ssize_t len, t_st *st, bool *buf)
{
    ssize_t     i;
    char        *next_line;

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

char    *compose_newl(char *str, ssize_t last_char, t_st *st)
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

char    *overwrite_left(ssize_t len, char *str, ssize_t i, t_st *st)
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

char    *concat_left(ssize_t len, char *str, t_st *st)
{
    char    *new_left;
    ssize_t i;
    ssize_t j;

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
