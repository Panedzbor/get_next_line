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

static t_st *create_el(t_st **st);
static t_st *search_fd(int fd, t_st **st);
static t_st *add_el(t_st **st);

t_st    *check_fd(int fd, t_st **start)
{
    t_st    *current;

    if (!*start)
        return(create_el(start));
    current = search_fd(fd, start);
    if (current)
        return (current);
    current = add_el(start);
    return (current);
}

static t_st *  create_el(t_st **ptr)
{
    *ptr = (t_st *)malloc(sizeof(t_st));
    if (!*ptr)
        return (NULL);
    (*ptr)[0].left = NULL;
    (*ptr)[0].next = NULL;
    return (*ptr);
}

static t_st *search_fd(int fd, t_st **start)
{
    t_st    *current;
    
    current = *start;
    while (current)
    {
        if (current->fd == fd)
            return (current);
        current = current->next;
    }
    return (NULL);
}

static t_st *add_el(t_st **start)
{
    t_st    *new_el;
    t_st    *last_el;

    create_el(&new_el);
    last_el = *start;
    while (last_el->next)
        last_el = last_el->next;
    last_el->next = new_el;
    return (new_el);
}

char    *del_el(t_st **start, t_st *to_remove, char *next_line)
{
    t_st    *current;

    if (*start != to_remove)
    {
        current = *start;
        while (current->next != to_remove)
            current = current->next;
        current->next = current->next->next;
    }
    else
        *start = (*start)->next;
    free((void *)to_remove);
    return (next_line);
}


void    init_struct(t_st *st, int fd)
{
    st->left = NULL;
    st->check = 0;
    st->fd = fd;
    st->blen = 0;
    st->str = NULL;
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