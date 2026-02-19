/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:44:56 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/19 14:04:44 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// FUNCIONES
char			*get_next_line(int fd);
char			*clear_static(char *complete_line);
char			*stop_jump_gnl(char *line);
char			*ft_strchr_gnl(const char *s, int c);
char			*ft_strjoin_gnl(char const *s1, char const *s2);
char			*ft_strdup_gnl(const char *s1);
size_t			ft_strlen_gnl(const char *string);

#endif