/* main.c - VERSIÓN LIMPIA PARA 42 */



/* #include "get_next_line.h"
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

//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test */







#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int		fd;
	char	*line;
	int		i;

	printf("--- PRUEBA 1: FD INVÁLIDO (Punto obligatorio) ---\n");
	line = get_next_line(42);
	if (line == NULL)
		printf("OK: FD 42 devolvió NULL\n");
	else
		printf("KO: FD 42 debería devolver NULL\n");

	printf("\n--- PRUEBA 2: ARCHIVO VACÍO ---\n");
	fd = open("empty.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
	fd = open("empty.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		printf("OK: Archivo vacío devolvió NULL\n");
	free(line);
	close(fd);

	printf("\n--- PRUEBA 3: LÍNEA LARGA (>2000 chars) ---\n");
	fd = open("long_line.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	i = 0;
	while (i++ < 2500)
		write(fd, "a", 1);
	write(fd, "\n", 1);
	close(fd);
	fd = open("long_line.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line && strlen(line) == 2501)
		printf("OK: Línea de 2501 caracteres leída correctamente\n");
	free(line);
	close(fd);

	printf("\n--- PRUEBA 4: 1 CARÁCTER SIN SALTO DE LÍNEA ---\n");
	fd = open("one_char.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, "x", 1);
	close(fd);
	fd = open("one_char.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line && strcmp(line, "x") == 0)
		printf("OK: Leyó 'x' sin añadir \\n al final\n");
	free(line);
	line = get_next_line(fd);
	if (line == NULL)
		printf("OK: Segunda lectura devolvió NULL\n");
	close(fd);

	printf("\n--- PRUEBA 5: LÍNEAS VACÍAS INTERMEDIAS ---\n");
	fd = open("empty_lines.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, "A\n\nB", 4);
	close(fd);
	fd = open("empty_lines.txt", O_RDONLY);
	line = get_next_line(fd); // "A\n"
	free(line);
	line = get_next_line(fd); // "\n"
	if (line && strcmp(line, "\n") == 0)
		printf("OK: Detectó correctamente la línea vacía (solo \\n)\n");
	free(line);
	line = get_next_line(fd); // "B"
	free(line);
	close(fd);

	printf("\n--- PRUEBA 6: STDIN (Escribe algo y pulsa Enter, o Ctrl+D para terminar) ---\n");
	printf("Escribe una línea: ");
	line = get_next_line(0);
	if (line)
	{
		printf("Leído de STDIN: %s", line);
		free(line);
	}

	printf("\n--- PRUEBA 7: MÚLTIPLES FDS (Bonus) ---\n");
	int fd1 = open("long_line.txt", O_RDONLY);
	int fd2 = open("one_char.txt", O_RDONLY);
	char *l1 = get_next_line(fd1);
	char *l2 = get_next_line(fd2);
	if (l1 && l2)
		printf("OK: Lectura simultánea de FD %d y FD %d\n", fd1, fd2);
	free(l1);
	free(l2);
	close(fd1);
	close(fd2);

	return (0);
} 

//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test

