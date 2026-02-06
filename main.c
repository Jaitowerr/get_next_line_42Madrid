#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("1char.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error al abrir el archivo\n");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("Resultado: %s", line);
		free(line);
	}
	//line = get_next_line(fd);
	printf("Resultado tras EOF: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("Resultado tras EOF++: %s", line);	
	free(line);

	close(fd);
	return (0);
}

//clear && cc -Wall -Werror -Wextra -D BUFFER_SIZE=10 get_next_line.c main.c -o gnl_test && ./gnl_test