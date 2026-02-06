/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:39:24 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/06 20:15:42 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *limpiar_static(char *linea_completa)
{
	char	*sobrante;
	int	i;
	
	i = 0;
	while (linea_completa[i] && linea_completa[i] != '\n')
		i++;
	if (!linea_completa[i] || !linea_completa[i + 1])
		return (NULL);
	sobrante = ft_strdup_gnl(&linea_completa[i + 1]);
	return (sobrante);
}

char    *get_next_line(int fd)
{
	static char *static_acumulado;
	char		*buffer;
	char		*linea;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		// printf("%d", BUFFER_SIZE);
		return (NULL);
	}
	linea = static_acumulado;
	static_acumulado = NULL; 
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (ft_strchr_gnl(linea, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 )
		{
			free(buffer);
			free(linea);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		linea = ft_strjoin_gnl(linea, buffer);
	}
	free(buffer);
	if (!linea || *linea == '\0')
	{
		free(linea);
		return (NULL);
	}
	static_acumulado = limpiar_static(linea);
	linea = stop_jump_gnl(linea);
	return (linea);
}





//clear && cc -Wall -Werror -Wextra -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c main.c -o gnl_test && ./gnl_test



// una temporal
// hacer join con la temporal
// luego cuando haya salto n almacenar en static
// luego recortar static
// si static tiene algo imprimir static mas el siguiente read

/*

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

char	*stop_jump_gnl(char *temp_acumulado)
{
	int		i;
	int		len;
	char	*jump;

	if (!temp_acumulado)
		return (NULL);

	jump = ft_strchr_gnl(temp_acumulado, '\n');

	if (jump)
		len = jump - temp_acumulado + 1;
	else
		len = ft_strlen_gnl(temp_acumulado);
	
	jump = malloc(sizeof(char) * (len + 1));
	if (!jump)
		return (NULL);

	i = 0;
	while (i < len)
	{
		jump[i] = temp_acumulado[i];
		i++;
	}
	jump[i] = '\0';
	return (jump);
}

char	*limpiar_static(char *static_acumulado)
{
	int	i;
	int	j;
	char *str;
	
	i = 0;
	while (static_acumulado[i] && static_acumulado[i] != '\n')
		i++;
	
	if (!static_acumulado[i])
	{
		free(static_acumulado);
		return (NULL);
	}
	
	str = malloc(sizeof(char *) * ft_strlen_gnl(static_acumulado) - i);
	if (!str)
		return (NULL);
	
	j = 0;
	while (static_acumulado[i])
		str[j++] = static_acumulado[++i];
	str[j] = '\0';
	free (static_acumulado);
	return (str);		

	
}

char	*get_next_line(int fd)
{
	static char	*static_acumulado;	//donde acumulamos la ultima lectura
	char		*linea;
	char		*buffer;	//temporal para leer del archivo
	ssize_t		bytes_read;	//guarda cuántos bytes ha leído read() en cada vuelta.
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	// if (!static_acumulado)
	// {
	// 	static_acumulado = malloc(sizeof(char) * 1);
	// 	if (!static_acumulado)
	// 		return (NULL);
	// 	static_acumulado[0] = '\0';
	// }
	linea = malloc(1);
	if (!linea)
		return (NULL);
	linea[0] = '\0';
	

	i = 0;
	bytes_read = 1;

	while (ft_strchr_gnl(linea, '\n') == NULL && bytes_read >= 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);		//devuelve cuántos bytes leyó, -1 si hay un error.
				{
			free (buffer);
			if (static_acumulado)
			{
				free (static_acumulado);
				static_acumulado = NULL;
			}
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (ft_strchr(buffer, '\n') != NULL)
		{
			static_acumulado = malloc(sizeof(char) * ft_strlen_gnl(static_acumulado - buffer) + 1);
			i = ft_strlen_gnl(static_acumulado);
			static_acumulado[i] = '\0';
		}
		linea = ft_strjoin_gnl(linea, buffer);
		
	
		
		
	}
	free(buffer);
	linea = stop_jump_gnl(static_acumulado);
	static_acumulado = limpiar_static(static_acumulado);
	// static_acumulado = linea;
	return (linea);
}
	*/