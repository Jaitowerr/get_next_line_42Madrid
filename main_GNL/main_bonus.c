

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



static void create_file(const char *filename, const char *content)
{
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Error creando archivo");
        exit(1);
    }
    if (write(fd, content, strlen(content)) == -1)
    {
        perror("Error escribiendo archivo");
        close(fd);
        exit(1);
    }
    close(fd);
}

int main(void)
{
    create_file("file1.txt", "Linea1_file1\nLinea2_file1\nLinea3_file1\n\n");
    create_file("file2.txt", "Linea1_file2\nLinea2_file2\n\n");
    create_file("file3.txt", "Linea1_file3\nLinea2_file3\nLinea3_file3\nLinea4_file3\n\n");

    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        perror("Error abriendo archivos");
        return 1;
    }

    char *line;
    int active = 3;

    while (active > 0)
    {
        if (fd1 >= 0)
        {
            line = get_next_line(fd1);
            if (line)
            {
                printf("file1: %s", line);
                free(line);
            }
            else
            {
                close(fd1);
                fd1 = -1;
                active--;
            }
        }

        if (fd2 >= 0)
        {
            line = get_next_line(fd2);
            if (line)
            {
                printf("file2: %s", line);
                free(line);
            }
            else
            {
                close(fd2);
                fd2 = -1;
                active--;
            }
        }

        if (fd3 >= 0)
        {
            line = get_next_line(fd3);
            if (line)
            {
                printf("file3: %s", line);
                free(line);
            }
            else
            {
                close(fd3);
                fd3 = -1;
                active--;
            }
        }
    }

    return 0;
}

//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus_test