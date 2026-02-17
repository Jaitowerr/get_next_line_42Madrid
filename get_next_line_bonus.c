/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:06:13 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/17 15:21:10 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*limpiar_static_bonus(char *line_completa)
{
	char	*sobrante;
	int		i;

	i = 0;
	while (line_completa[i] && line_completa[i] != '\n')
		i++;
	if (!line_completa[i] || !line_completa[i + 1])
		return (NULL);
	sobrante = ft_strdup_gnl_bonus(&line_completa[i + 1]);
	return (sobrante);
}

static char	*read_and_accumulate_bonus(int fd, char *acum_linea, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr_gnl_bonus(acum_linea, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(acum_linea);
			acum_linea = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		acum_linea = ft_strjoin_gnl_bonus(acum_linea, buffer);
	}
	if (!acum_linea || *acum_linea == '\0')
	{
		free(acum_linea);
		return (NULL);
	}
	return (acum_linea);
}

char	*get_next_line(int fd)
{
	static char	*acum_line[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_and_accumulate_bonus(fd, acum_line[fd], buffer);
	free(buffer);
	if (!line)
	{
		acum_line[fd] = NULL;
		return (NULL);
	}
	acum_line[fd] = limpiar_static_bonus(line);
	line = stop_jump_gnl_bonus(line);
	return (line);
}
