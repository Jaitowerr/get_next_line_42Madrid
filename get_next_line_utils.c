/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:44:59 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/06 19:21:07 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *string)
{
	size_t  length;

	if (!string)
		return (0);
	length = 0;
	while (string[length] != '\0')
		length++;
	return (length);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*dest;
	size_t	i;

	if (!s1)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strjoin_gnl(char const *s1, char const *s2)
{
	char    *s3;
	size_t  i1;
	size_t  i2;
	size_t  i3;
	
	i1 = ft_strlen_gnl(s1);
	i2 = ft_strlen_gnl(s2);
	s3 = malloc(sizeof(char) *(i1 + i2 + 1));
	if (!s3)
		return (NULL);
	i1 = 0;
	i2 = 0;
	i3 = 0;
	while (s1 && s1[i1])
		s3[i3++] = s1[i1++];
	while (s2 && s2[i2])
		s3[i3++] = s2[i2++];
	s3[i3] = '\0';
	free((char *)s1);
	return (s3);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int i = 0;
	if (!s) return (NULL);
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

char	*stop_jump_gnl(char *linea)
{
	int     i;
	char    *str;

	if (!linea || !*linea)
		return (NULL);
	i = 0;
	while (linea[i] && linea[i] != '\n')
		i++;
	if (linea[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (linea[i] && linea[i] != '\n')
	{
		str[i] = linea[i];
		i++;
	}
	if (linea[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	free(linea);
	return (str);
}
