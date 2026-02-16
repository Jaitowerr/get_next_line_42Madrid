/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 23:55:13 by aitorres          #+#    #+#             */
/*   Updated: 2026/02/17 00:25:24 by aitorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	fd = open("1char.txt", O_RDONLY); // Abrimos el archivo prueba.txt en modo solo lectura
	if (fd == -1)
	{
		printf("Error al abrir el archivo");
		return (1);
	}

	printf("--- Iniciando lectura de prueba.txt ---\n");

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Línea [%d]-->%s", i, line);
        free(line);  // ¡Muy importante liberar la memoria! --> Leer el Readme, contiene INSTRUCCIONES exigidas por 42Madrid.
		i++;
	}

	close(fd);
	printf("\n--- Fin de la lectura ---\n");
	return (0);
}

//gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test