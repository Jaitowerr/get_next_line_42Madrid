/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:39:24 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/04 18:39:27 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"





size_t	ft_strlen_gnl(const char *string)
{
	size_t	length;

	if (!string)
		return (0);
	length = 0;
	while (string[length] != '\0')
		length++;
	return (length);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i1;
	size_t	i2;
	size_t	i3;

	i1 = ft_strlen_gnl(s1);
	i2 = ft_strlen_gnl(s2);
	s3 = malloc(sizeof(char) *(i1 + i2 + 1));
	if (!s3)
		return (NULL);
	i1 = 0;
	i2 = 0;
	i3 = 0;
	while (s1[i1])
		s3[i3++] = s1[i1++];
	while (s2[i2])
		s3[i3++] = s2[i2++];
	s3[i3] = '\0';
	free((char *)s1);
	return (s3);
}



char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*stop_jump_gnl(char *acumulado)
{
	int		i;
	int		len;
	char	*jump;

	if (!acumulado)
		return (NULL);

	jump = ft_strchr_gnl(acumulado, '\n');

	if (jump)
		len = jump - acumulado + 1;
	else
		len = ft_strlen_gnl(acumulado);
	
	jump = malloc(sizeof(char) * (len + 1));
	if (!jump)
		return (NULL);

	i = 0;
	while (i < len)
	{
		jump[i] = acumulado[i];
		i++;
	}
	jump[i] = '\0';
	return (jump);
}



char	*get_next_line(int fd)
{
	static char	*acumulado;	//donde acumulamos lo que leemos
	char		*buffer;	//temporal para leer del archivo
	ssize_t		bytes_read;	//guarda cuántos bytes ha leído read() en cada vuelta.

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	if (!acumulado)
	{
		acumulado = malloc(sizeof(char) * 1);
		if (!acumulado)
			return (NULL);
		acumulado[0] = '\0';
	}

	bytes_read = 1;

	while (ft_strchr_gnl(acumulado, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);		//devuelve cuántos bytes leyó, -1 si hay un error.
		if (bytes_read == -1)
		{
			free (buffer);
			if (acumulado)
			{
				free (acumulado);
				acumulado = NULL;
			}
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		acumulado = ft_strjoin_gnl(acumulado, buffer);
	}
	free(buffer);
	return (stop_jump_gnl(acumulado));
}


//clear && cc -Wall -Werror -Wextra -D BUFFER_SIZE=10 get_next_line.c main.c -o gnl_test && ./gnl_test