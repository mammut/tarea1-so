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

##3. Notas##
La función scandir() es un wrapper para la llamada al sistema que permite obtener metainformacion de carpetas y archivos. Para mayor referencia dirigirse a [The Open Group Base Specifications Issue 7][1].

Esta función utiliza **malloc()** para generar un arreglo de estructuras dirent. Estas deben ser liberadas después de ser utilizadas.

Para verificar fugas de memoria se utilizo valgrind en Linux de la siguiente forma:

    make clean
    make
    valgrind ./tarea1
    ==9724== Memcheck, a memory error detector
    ==9724== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
    ==9724== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
    ==9724== Command: ./tarea1
    ==9724==
    ==9724==
    ==9724== HEAP SUMMARY:
    ==9724==     in use at exit: 0 bytes in 0 blocks
    ==9724==   total heap usage: 31 allocs, 31 frees, 263,940 bytes allocated
    ==9724==
    ==9724== All heap blocks were freed -- no leaks are possible
    ==9724==
    ==9724== For counts of detected and suppressed errors, rerun with: -v
    ==9724== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

valgrind nos demuestra que no hubo fugas de memoria:
>All heap blocks were freed -- no leaks are possible

[1]: http://pubs.opengroup.org/onlinepubs/9699919799/functions/scandir.html