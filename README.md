# 📖 Get_next_line

## Descripción

Este proyecto trata sobre la creación de una función que permite leer una línea de un archivo descriptor de una sola vez.

La función recibe un descriptor de archivo y devolvera la siguiente línea del archivo como una cadena de caracteres terminada en null o `\n`.

<b>Prototipo de la función:</b>


	char	*get_next_line(int fd)

En esta función le enviamos el `int fd` (File Descriptor). Un fd es simplemente un número entero que el sistema operativo usa para identificar un canal de comunicación abierto:

* `0` (Standard Input / stdin): Es el teclado. Si lees de aquí, el programa espera a que escribas algo.
* `1` (Standard Output / stdout): Es la pantalla (salida normal).
* `2` (Standard Error / stderr): Es la pantalla también, pero reservada para mensajes de error.
* `3` en adelante: Son archivos que tú abres con la función open(). Por ejemplo, si abres texto.txt, el sistema te dará el fd 3. Si abres otro, el 4, y así.

Dentro de nuestra función utilizaremos variables `static`.

El comportamiento de la función puede depender de varios factores, si el fd que le enviamos es `v0`y BUFFER_SIZE `<= 0`entonces devolvemos NULL;


* ### ¿Qué es el BUFFER_SIZE?

	Si BUFFER_SIZE=1, lees el archivo letra a letra (muy lento).

	Si BUFFER_SIZE=100, lees de 100 en 100 caracteres.

	¿Para qué sirve? La función read() necesita saber cuántos bytes debe intentar leer de golpe.


## read()

	Lee datos desde un file descriptor (un archivo, el teclado, etc.) y los mete en un buffer (un trozo de memoria que tú le das).

		ssize_t read(int fildes, void *buf, size_t nbyte);

	int fildes (file descriptor):  Si le pasas un fd inválido (negativo o cerrado), read devuelve -1.
	void *buf (buffer): Es la dirección de memoria donde read va a escribir los datos que lea. Hay que haber hecho malloc antes para reservar ese espacio.
	size_t nbyte: Es el máximo de bytes que quieres leer de golpe. `BUFFER_SIZE`

### ¿Qué devuelve read()? (tipo ssize_t)
* `Número > 0`: Cuántos bytes ha leído realmente. Ejemplo: pides 10, pero solo quedan 3 en el archivo → devuelve 3.
* `0`: Has llegado al final del archivo (EOF). No hay más datos.
* `-1`: Ha ocurrido un error (archivo cerrado, fd inválido, etc.).

Porque read puede devolver valores grandes (archivos enormes) y también -1 (error). ssize_t es el tipo "con signo" diseñado específicamente para esto.









## open ()

Para que la función funcione, primero debes implementar la siguiente biblioteca

		#include <fcntl.h>

Esta función le permitirá abrir y acceder a un archivo. Su prototipo es el siguiente:


### Copiar
int open (const char* path, int flags [, int mode ]);
###const char* path
Corresponde al título del archivo que desea abrir/crear.

También se refiere a la ubicación del archivo. Si no trabaja en el mismo directorio que el archivo, puede proporcionar una ruta absoluta que comience con "/".

### int flags [, int mode ]
Debes indicarle a tu función el tipo de acceso que deseas. Esto se hace mediante indicadores. Aquí está la lista con la información de cada indicador:

* O_RDONLY : En modo de solo lectura, abre el archivo.

* O_WRONLY : En modo de solo escritura, abre el archivo

* O_RDWR : Abre el archivo en modo de lectura y escritura

* O_CREAT : Esta bandera se aplica para crear un archivo si no existe en la ruta o directorio especificado

* O_EXCL : Evita la creación de un archivo si ya existe en el directorio o ubicación.

### Valor de retorno
El valor de retorno de open() es un descriptor de archivo, un entero pequeño y no negativo que sirve de índice a una entrada en la tabla de descriptores de archivos abiertos del proceso. Si se produce un error, la función devolverá -1 como sinónimo de fallo.

		int main()
		{
			int fd;
			fd = open("text.txt", O_RDONLY);
		}

### read ()

Es la función del sistema que lee bytes desde un file descriptor (fd) hacia un buffer en memoria. Viene de la cabecera <unistd.h>.

La función está prototipada de esta manera:

		ssize_t read(int fildes, void *buf, size_t nbyte);

Retorna:
* `1`: número de bytes leídos.
* `0`: EOF (final del archivo).
* `-1` : error (ej: descriptor inválido, interrupción, etc.).

Esta función intenta leer nbytebytes de datos del objeto referenciado por el descriptor fildesen el búfer apuntado por buf. La función read() comienza en la posición dada por el puntero asociado a fildes. Al final, el puntero se incrementa según el número de bytes ( nbyte) leídos.

<br><br>





## Static variables
