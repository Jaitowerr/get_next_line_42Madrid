/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:44:56 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/17 15:22:52 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h> // Para malloc y free
# include <unistd.h> // Para read
# include <stddef.h>   /* size_t */
# include <fcntl.h>  // Para open

# ifndef FD_LIMIT
#  define FD_LIMIT 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// FUNCIONES
char			*limpiar_static_bonus(char *line_grande);
char			*stop_jump_gnl_bonus(char *line);
char			*ft_strchr_gnl_bonus(const char *s, int c);
char			*ft_strjoin_gnl_bonus(char const *s1, char const *s2);
char			*ft_strdup_gnl_bonus(const char *s1);
size_t			ft_strlen_gnl_bonus(const char *string);
char			*get_next_line(int fd);

#endif
