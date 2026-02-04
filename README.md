

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

## read ()
La función está prototipada de esta manera:

		ssize_t read(int fildes, void *buf, size_t nbyte);

Esta función intenta leer nbytebytes de datos del objeto referenciado por el descriptor fildesen el búfer apuntado por buf. La función read() comienza en la posición dada por el puntero asociado a fildes. Al final, el puntero se incrementa según el número de bytes ( nbyte) leídos.

<br><br>





## Static variables