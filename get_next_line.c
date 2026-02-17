/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:39:24 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/17 14:46:29 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*limpiar_static(char *line_completa)
{
	char	*sobrante;
	int		i;

	i = 0;
	while (line_completa[i] && line_completa[i] != '\n')
		i++;
	if (!line_completa[i] || !line_completa[i + 1])
		return (NULL);
	sobrante = ft_strdup_gnl(&line_completa[i + 1]);
	return (sobrante);
}

static char	*read_and_accumulate(int fd, char *acum_line, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr_gnl(acum_line, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(acum_line);
			acum_line = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		acum_line = ft_strjoin_gnl(acum_line, buffer);
	}
	if (!acum_line || *acum_line == '\0')
	{
		free(acum_line);
		return (NULL);
	}
	return (acum_line);
}

char	*get_next_line(int fd)
{
	static char	*acum_line;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(acum_line);
		acum_line = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_and_accumulate(fd, acum_line, buffer);
	free(buffer);
	if (!line)
	{
		acum_line = NULL;
		return (NULL);
	}
	acum_line = limpiar_static(line);
	line = stop_jump_gnl(line);
	return (line);
}
