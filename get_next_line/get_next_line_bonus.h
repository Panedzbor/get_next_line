/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/18 14:23:51 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNLB_H
# define GNLB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_statvals
{
    char                *left;
    int                 check;
    char                buffer[BUFFER_SIZE + 1];
    int                 fd;
    ssize_t             blen;
    struct s_statvals   *next;
} t_st;

char    *get_next_line(int fd);
void    init_struct(t_st *st, int fd);
ssize_t count_size(char *str);
char    *erase_left(t_st *st);
int     check_fd(int fd, t_st **st);

#endif
