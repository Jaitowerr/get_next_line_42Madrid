/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:39:24 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/16 13:52:52 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*limpiar_static(char *linea_completa)
{
	char	*sobrante;
	int		i;

	i = 0;
	while (linea_completa[i] && linea_completa[i] != '\n')
		i++;
	if (!linea_completa[i] || !linea_completa[i + 1])
		return (NULL);
	sobrante = ft_strdup_gnl(&linea_completa[i + 1]);
	return (sobrante);
}

static char	*leer_y_acumular(int fd, char *acum_linea, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (ft_strchr_gnl(acum_linea, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(acum_linea);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		acum_linea = ft_strjoin_gnl(acum_linea, buffer);
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
	static char	*acum_line;
	char		*linea;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	linea = leer_y_acumular(fd, acum_line, buffer);
	free(buffer);
	if (!linea)
	{
		acum_line = NULL;
		return (NULL);
	}
	acum_line = limpiar_static(linea);
	linea = stop_jump_gnl(linea);
	return (linea);
}
