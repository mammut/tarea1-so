#Tarea 1 SO#

Para el presente laboratorio se realizó un programa en C utilizando llamadas a sistema en Linux. El estudiante aprendió a manejarse a través del sistema de archivos y también la manipulación de directorios y archivos. El programa realizado recorrer los directorios ubicados dentro de una ruta dada y guarda en distintos archivos información relacionada a su contenido.

##1. Compilación##

Para compilar el código basta ir al directorio donde se encuentra el makefile y ejecutar el siguiente comando en el terminal:

    make

Esto realizara el proceso de compilación y linkeado de los archivos fuente.
Si se desea restablecer la carpeta al estado original basta hacer esto en el terminal:

    make clean


Esto elimina todos los archivos **.o**, la carpeta **Informacion** y su contenido y el ejecutable **tarea1**.

##2. Ejecución##
Para ejecutar el programa ya compilado se puede hacer de 3 formas.

 - Sin argumentos: Ejecuta el programa utiliza la ruta actual por defecto:
 - Con ruta relativa: Se entrega como argumento la ruta relativa.
 - Con ruta absoluta: Se entrega como argumento la ruta absoluta.

Ejemplos (en el orden de la lista anterior):

    ./tarea1
    ./tarea1 ./A/B
    ./tarea1 /Users/me/Desktop/tarea1/A


La funcion scandir() es un wrapper para la llamada al sistema que permite obtener metainformacion de carpetas y archivos. Para mayor referencia dirigirse a [The Open Group Base Specifications Issue 7][1]

[1]: http://pubs.opengroup.org/onlinepubs/9699919799/functions/scandir.html