/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:25:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/22 14:23:51 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int  first_el(t_st *st);
static int  search_fd(int fd, t_st *st);
static int  add_el(int fd, t_st *st);
static int  copy_el(t_st *new, t_st *st, int fd);
static void copy_buf(t_st *new, t_st *st, int i);

int check_fd(int fd, t_st *st)
{
    int index;

    if (!st)
        return(first_el(st));
    index = search_fd(fd, st);
    if (index >= 0)
        return (index);
    index = add_el(fd, st);
    return (index);
}

static int  first_el(t_st *st)
{
    st = (t_st *)malloc(sizeof(t_st));
    if (!st)
        return (NULL);
    st->next = NULL;
    return (0);
}

static int  search_fd(int fd, t_st *st)
{
    int i;

    i = 0;
    while (true)
    {
        if (st[i].fd == fd)
            return (i);
        if (!st[i].next)
            break ;
        i++;
    }
    return (-1);
}

static int  add_el(int fd, t_st *st)
{
    int i;
    t_st *new;

    i = 0;
    while (true)
    {
        if (!st[i++].next)
            break ;
    }
    new = (t_st *)malloc((i + 2) * sizeof(t_st));
    if (!new)
        return (NULL);
    i = copy_el(new, st, fd);
    free ((void*)st);
    st = new;
    return (i);
}

static int  copy_el(t_st *new, t_st *st, int fd)
{
    int i;

    i = 0;
    while (true)
    {
        new[i].left = st[i].left;
        new[i].check = st[i].check;
        copy_buf(new, st, i);
        new[i].fd = st[i].fd;
        new[i].next = st[i].next;
        if (!st[i].next)
            break ;
        i++;
    }
    new[i].next = &new[i + 1];
    new[++i].next = NULL;
    return (i);
}

static void copy_buf(t_st *new, t_st *st, int i)
{
    int j;
    
    j = 0;
    while (true)
    {
        new[i].buffer[j] = st[i].buffer[j];
        if (st[i].buffer[j] == '\0')
            break ;
        j++;
    }
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

char    *erase_left(t_st *st)
{
    if (st->left)
        free((void *)st->left);
    st->check = 0;
    return (NULL);   
}