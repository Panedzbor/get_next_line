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

static char *search_newl(t_st *cur, ssize_t len, t_st **st, bool *buf);
static char *compose_newl(char *str, ssize_t last_char, t_st *st);
static char *overwrite_left(ssize_t len, char *str, ssize_t i, t_st *st);
static char *concat_left(ssize_t len, char *str, t_st *st);

char    *get_next_line(int fd)
{
    ssize_t     len;
    static t_st *st;
    t_st        *cur;
    bool        buf;

    cur = check_fd(fd, &st);
    if (!cur->left)
        init_struct(cur, fd);
    buf = false;
    if (!cur->left || cur->check != 0)
    {
        len = read(fd, cur->buffer, BUFFER_SIZE);
        cur->blen = len;
        if (len <= 0 && !cur->left)
            return (del_el(&st, cur, NULL));
        cur->buffer[len] = '\0';
        buf = true;
        cur->str = cur->buffer;
    }
    else
    {
        len = count_size(cur->left);
        cur->str = cur->left;
    }
    return (search_newl(cur, len, &st, &buf));
}

char    *search_newl(t_st *cur, ssize_t len, t_st **st, bool *buf)
{
    ssize_t     i;

    i = 0;
    while (i < len)
    {
        if (cur->str[i] == '\n' 
            || (cur->blen < BUFFER_SIZE && cur->str[i + 1] == '\0'))
        {
            if (!*buf)
                cur->check = 1;
            char *nl = compose_newl(cur->str, i, cur);
            cur->left = overwrite_left(len, cur->str, i, cur);
            if (cur->blen < BUFFER_SIZE && cur->str[i + 1] == '\0')
                del_el(st, cur, NULL);
            return (nl);
        }
        i++;
    }
    if (cur->blen == 0)
        return (del_el(st, cur, compose_newl(cur->str, -1, cur)));
    if (!*buf)
        cur->check = -1;
    else
        cur->left = concat_left(len, cur->str, cur);
    return (get_next_line(cur->fd));
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
