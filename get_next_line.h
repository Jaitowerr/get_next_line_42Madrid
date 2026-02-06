/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:44:56 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/06 15:42:17 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // Para malloc y free
# include <unistd.h> // Para read
# include <stddef.h>   /* size_t */
# include <fcntl.h>  // Para open

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif


// FUNCIONES
char			*get_next_line(int fd);
char    		*limpiar_static(char *linea_grande);
char			*stop_jump_gnl(char *linea);
char			*ft_strchr_gnl(const char *s, int c);
char 			*ft_strjoin_gnl(char const *s1, char const *s2);
char			*ft_strdup_gnl(const char *s1);
size_t			ft_strlen_gnl(const char *string);


#endif