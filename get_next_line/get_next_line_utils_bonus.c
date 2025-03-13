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
#include <stdio.h>

static t_st	*create_el(t_st **ptr);

t_st	*check_fd(int fd, t_st **start)
{
	t_st	*current;
	t_st	*new_el;
	t_st	*last_el;

	if (!*start)
		return (create_el(start));
	current = *start;
	while (current)
	{
		if (current->fd == fd)
			break ;
		current = current->next;
	}
	if (current)
		return (current);
	create_el(&new_el);
	last_el = *start;
	while (last_el->next)
		last_el = last_el->next;
	last_el->next = new_el;
	return (new_el);
}

static t_st	*create_el(t_st **ptr)
{
	*ptr = (t_st *)malloc(sizeof(t_st));
	if (!*ptr)
		return (NULL);
	(*ptr)[0].left = NULL;
	(*ptr)[0].next = NULL;
	return (*ptr);
}

void	init_free(t_st *st, int fd, void *ptr)
{
	if (!ptr)
	{
		st->left = NULL;
		st->check = 0;
		st->fd = fd;
		st->blen = 0;
		return ;
	}
	free(ptr);
	ptr = NULL;
}

ssize_t	count_size(char *str)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*erase_left(t_st *st, t_st **start, char *next_line)
{
	t_st	*current;

	if (!start)
	{
		if (st->left)
			init_free(NULL, 0, (void *)st->left);
		st->check = 0;
		return (NULL);
	}
	if (st->left)
		init_free(NULL, 0, (void *)st->left);
	if (*start != st)
	{
		current = *start;
		while (current->next != st)
			current = current->next;
		current->next = current->next->next;
	}
	else
		*start = (*start)->next;
	init_free(NULL, 0, (void *)st);
	return (next_line);
}
