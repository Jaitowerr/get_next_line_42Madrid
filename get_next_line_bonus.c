/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:06:13 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/13 19:42:45 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*limpiar_static_bonus(char *linea_completa)
{
	char	*sobrante;
	int		i;

	i = 0;
	while (linea_completa[i] && linea_completa[i] != '\n')
		i++;
	if (!linea_completa[i] || !linea_completa[i + 1])
		return (NULL);
	sobrante = ft_strdup_gnl_bonus(&linea_completa[i + 1]);
	return (sobrante);
}

static char	*leer_y_acumular_bonus(int fd, char *linea, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr_gnl_bonus(linea, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(linea);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		linea = ft_strjoin_gnl_bonus(linea, buffer);
	}
	if (!linea || *linea == '\0')
	{
		free(linea);
		return (NULL);
	}
	return (linea);
}

char	*get_next_line(int fd)
{
	static char	*acum_line[1024];
	char		*linea;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	linea = leer_y_acumular_bonus(fd, acum_line[fd], buffer);
	free(buffer);
	if (!linea)
	{
		acum_line[fd] = NULL;
		return (NULL);
	}
	acum_line[fd] = limpiar_static_bonus(linea);
	linea = stop_jump_gnl_bonus(linea);
	return (linea);
}
