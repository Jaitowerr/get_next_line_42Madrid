/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:06:13 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/19 14:21:28 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clear_static_bonus(char *complete_line)
{
	char	*spare;
	int		i;

	i = 0;
	while (complete_line[i] && complete_line[i] != '\n')
		i++;
	if (!complete_line[i] || !complete_line[i + 1])
		return (NULL);
	spare = ft_strdup_gnl_bonus(&complete_line[i + 1]);
	return (spare);
}

static char	*read_and_accumulate_bonus(int fd, char *acum_line, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr_gnl_bonus(acum_line, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(acum_line);
			acum_line = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		acum_line = ft_strjoin_gnl_bonus(acum_line, buffer);
	}
	if (!acum_line || *acum_line == '\0')
	{
		free(acum_line);
		acum_line = NULL;
		return (NULL);
	}
	return (acum_line);
}

char	*get_next_line(int fd)
{
	static char	*acum_line[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd >= FD_LIMIT || BUFFER_SIZE <= 0)
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
	acum_line[fd] = clear_static_bonus(line);
	line = stop_jump_gnl_bonus(line);
	return (line);
}
