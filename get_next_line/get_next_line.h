/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:22:47 by earutiun          #+#    #+#             */
/*   Updated: 2025/02/18 14:23:51 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

//# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_statvals
{
    char    *left;
    int     check;
    char    buffer[BUFFER_SIZE + 1];
    int     fd;
} t_st;

char    *get_next_line(int fd);

#endif
