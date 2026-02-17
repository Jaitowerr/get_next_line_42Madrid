*Este proyecto ha sido creado como parte del currículo de 42 por aitorres*

# 📖 Get_next_line

# Descripción

El proyecto Get Next Line (GNL) es un ejercicio fundamental en la formación de 42 Madrid que consiste en implementar una función en C capaz de leer un archivo línea por línea. Esta función, llamada get_next_line, debe gestionar la lectura de manera eficiente utilizando un buffer de tamaño configurable y manejar correctamente la memoria dinámica.

<b>Prototipo de la función:</b>

	char	*get_next_line(int fd)

Cadaa función recibe un descriptor de archivo (fd) y devuelve la siguiente línea completa, incluyendo el salto de línea `\n` si existe. Cuando se alcanza el final del archivo o ocurre un error, la función devuelve `NULL`.

Internamente, utiliza una variable estática para almacenar los datos sobrantes de la lectura anterior, permitiendo continuar donde se dejó en la siguiente llamada.

## Objetivos del proyecto

* Comprender el manejo de descriptores de archivo en C.
* Practicar la gestión dinámica de memoria con malloc y free.
* Implementar una función que mantenga el estado entre llamadas usando variables estáticas.
* Leer archivos de texto línea a línea, incluyendo líneas largas que superen el tamaño del buffer.
* Manejar correctamente los saltos de línea y el final del archivo.
* Evitar fugas de memoria y errores de acceso.

<hr><hr><br>


## 💡Conceptos Clave

### 1. File Descriptors (fd)

Un fd es un número entero que el sistema operativo usa para identificar un canal de comunicación abierto:

* 0 (Standard Input): Teclado.
* 1 (Standard Output): Pantalla.
* 2 (Standard Error): Pantalla (errores).
* 3 en adelante: Archivos abiertos con open().
<br><br><hr>

### 2. ¿Qué es el BUFFER_SIZE?

Es la cantidad de bytes que la función read() intenta leer de golpe.

* Si BUFFER_SIZE=1: Lee letra a letra (muy lento).
* Si BUFFER_SIZE=100: Lee de 100 en 100 caracteres.
* Caso de error: Si el fd es inválido o BUFFER_SIZE <= 0, la función devuelve NULL.
<br><br><hr>


### 3. Variables Estáticas (static)

Se utilizan para que la función "recuerde" lo que leyó en la llamada anterior. A diferencia de una variable local normal, una static no se destruye cuando la función termina.

<hr><hr><br><br>

## 🛠️ Funciones del Sistema Utilizadas

### open()
Para usarla necesitas `#include <fcntl.h>`. Permite abrir un archivo y obtener su fd.

Flags comunes:

	O_RDONLY (Solo lectura)
	O_WRONLY (Solo escritura)
	O_RDWR (Lectura y escritura).

* Retorno: El fd (entero positivo) o -1 si hay error.


### read()

Viene de `#include <unistd.h>`. Lee datos desde un fd hacia un buffer.

	ssize_t read(int fd, void *buf, size_t count);

* Retorno (> 0):  Número de bytes leídos realmente.

* Retorno (0): Final del archivo (EOF).

* Retorno (-1): Error.

<br><hr><hr><br><br>


# INSTRUCCIONES
Instrucciones para compilar y ejecutar el programa de prueba de get_next_line, lee atentatemente, es responsabilidad del rpogramador que lo utilice, en leer las instrucciones para su correcto funcionameinto.
<br><br>

## 1. Compilar

Abre una terminal en la carpeta donde están los archivos y ejecuta el siguiente comando para compilar el programa de prueba junto con la implementación de get_next_line y sus utilidades:

	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test

* Puedes cambiar el valor de BUFFER_SIZE para probar diferentes tamaños de buffer.
* Asegúrate de que main.c contiene el código de prueba que llama a get_next_line con el archivo prueba.txt.
`---`
<br><br>
## 2. Crear el archivo de prueba

Crea un archivo llamado `prueba.txt` en la misma carpeta con el siguiente contenido para probar diferentes casos.

Escribe lo que quieras en él, puedes escribir o copiar en él El Quijote.
<br><br>


## 3. Ejecutar

Ejecuta el programa compilado con:

	./gnl_test

Si utilizas el main facilitado por el programador aitorres, el programa leerá prueba.txt línea a línea y lo mostrará en pantalla.
<br><br>

## 4. Liberar memoria

Recuerda que cada línea devuelta por get_next_line debe ser liberada con free() para evitar fugas de memoria. Revisa que cada iteración que hagas en el main para llamarlo debe tener su free correspondiente, por si queda alguna duda, así:

	line = get_next_line(fd);
	free(line);

<br><br>

## 5. Comprobar fugas de memoria

Puedes usar valgrind para verificar que no haya fugas de memoria

	valgrind --leak-check=full ./gnl_test


<br><br>

Por si quedan dudas, te muestro el main con cada iteración

	int	main(void)
	{
		int		fd;
		char	*line;
		int		i;
		
		printf("--- Iniciando lectura de prueba.txt ---\n");

		while ((line = get_next_line(fd)) != NULL)
		{
			printf("Línea [%d]-->%s", i, line);
			free(line);  // ¡Muy importante liberar la memoria! --> Leer el Readme, contiene INSTRUCCIONES en README exigidas por 42Madrid.
			i++;
		}

		close(fd);
		printf("\n--- Fin de la lectura ---\n");
		return (0);
	}
<br><br>

## 6. 🛡️ Robustez y Gestión de Errores

Para asegurar que el programa no tenga fugas de memoria (**Memory Leaks**) ni punteros colgantes (**Dangling Pointers**), la implementación sigue esta lógica de control:

| Situación | Acción en el Código | Resultado |
| :--- | :--- | :--- |
| **Fallo en `read()`** | Se libera la variable estática y se retorna `NULL`. | `acum_line` queda a `NULL`, evitando punteros inválidos. |
| **Fallo en `malloc` (`strjoin`)** | La función `ft_strjoin_gnl` libera el parámetro `s1` antes de retornar `NULL`. | Se evita la fuga de la memoria acumulada hasta ese momento. |
| **Final de Archivo (EOF)** | Se procesa el último tramo y se libera la estática en la última llamada. | Limpieza total del heap al terminar la lectura. |
| **Línea devuelta al usuario** | La función `stop_jump_gnl` libera la cadena original y devuelve solo la línea necesaria. | Gestión eficiente de la memoria dinámica. |
| **Uso de `BUFFER_SIZE`** | Se reserva memoria dinámicamente para el buffer en cada llamada y se libera al final. | El programa es independiente del tamaño del buffer definido al compilar. |

<br><br>

**El main.c suministrado tiene dos partes, lal descrita anteriormente comentada y una mas profunda descomentada lista para ejecutar, podrá observar todos los casos de null y otros, creación de .txt automáticos para las pruebas. Eso si, siempre sigue las instrucciones liberando memoria tras imprimir cada linea

> **Nota para los evaluadores:** Las funciónes como `ft_strjoin_gnl` ha sido diseñada específicamente modificando la original para este proyecto, encargándose de liberar la memoria del acumulador anterior (`s1`) automáticamente en cada concatenación, simplificando así el flujo principal y previniendo fugas.

<br><hr><hr><br><br>

## 📚 Recursos y Uso de IA


*   Distintas fuentes de internet, guia 42, paginas de google, videos de youtube.
*   **Man pages:** `man 2 read`, `man 2 open`, `man 2 close`.
*   **Tutoriales de 42:** Guías de la comunidad sobre el uso de variables estáticas y gestión de memoria en C.
* Páginas de IA como Gémini o Claude Sonnet para ayuda en construccion de reducción de funciones tras fallos y muchas dudas, y organizando los conceptos teóricos (fd, static, read) de forma pedagógica. Resolución de dudas conceptuales sobre la librería `<fcntl.h>` y el comportamiento de los flags de apertura de archivos.
