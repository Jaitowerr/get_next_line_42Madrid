#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error al abrir el archivo\n");
		return (1);
	}
	
	line = get_next_line(fd);
	printf("Resultado: %s\n", line);
	free(line);
	
	close(fd);
	return (0);
}

//clear && cc -Wall -Werror -Wextra -D BUFFER_SIZE=10 get_next_line.c main.c -o gnl_test && ./gnl_test