/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:44:56 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/04 18:45:56 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // Para malloc y free
# include <unistd.h> // Para read
# include <stddef.h>   /* size_t */
# include <fcntl.h>  // Para open

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


// FUNCIONES
char	*get_next_line(int fd);


#endif