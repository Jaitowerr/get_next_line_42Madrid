#include <fcntl.h>    // Para open
#include <unistd.h>   // Para read y write
#include <stdlib.h>   // Para malloc y free
#include <stdio.h>    // Para printf

int main(void)
{
    int     fd;
    int     bytes_leidos;
    char    buffer[11]; // Vamos a leer de 10 en 10 (10 + 1 para el \0)

    // 1. Abrimos un archivo (asegúrate de tener un archivo llamado test.txt)
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error al abrir el archivo\n");
        return (1);
    }

    printf("--- EMPEZANDO LA LECTURA ---\n");

    // 2. El bucle de lectura
    // read devuelve cuántos bytes ha leído. Mientras sea > 0, seguimos.
    bytes_leidos = read(fd, buffer, 10);
    while (bytes_leidos > 0)
    {
        // Ponemos el nulo al final de lo que hayamos leído para poder usar printf
        buffer[bytes_leidos] = '\0';
        
        printf("He leido %d bytes. Contenido: [%s]\n", bytes_leidos, buffer);
        
        // Volvemos a pedir otros 10 bytes
        bytes_leidos = read(fd, buffer, 10);
    }

    // 3. Cuando bytes_leidos es 0, el bucle termina (Final del archivo)
    if (bytes_leidos == 0)
        printf("--- FIN DEL ARCHIVO (EOF) ---\n");
    else
        printf("--- ERROR EN LA LECTURA ---\n");

    close(fd);
    return (0);
}

//clear && cc prueba_read.c -o prueba && ./prueba