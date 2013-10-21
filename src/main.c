#include <stdlib.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "../include/imprimidor.h"
#include "../include/filters.h"
#include "../include/main.h"
/**
 * Dejamos los tres archivos globales, asi no es necesario pasarlos como parametros en la funcion recursiva
 */
FILE *recorrido;
FILE *directorios;
FILE *archivos;

int main (int argc, char *argv[])
{
  /* 1. Crear carpeta Informacion en el caso de que no exista */
  if ( mkdir("Informacion", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
    if (errno != EEXIST) {
      perror("No se pudo crear la carpeta informacion, por favor revise que tenga permisios necesarios\n");
      return EXIT_FAILURE;
    }
  }

  /* 2. Intentar abrir los archivos de texto de output */
  if ( ! (recorrido = fopen("Informacion/recorrido.txt", "w")) ) {
    perror("No se pudo abrir el archivo Informacion/recorrido.txt");
    return EXIT_FAILURE;
  }

  if ( ! (directorios = fopen("Informacion/directorios.txt", "w")) ) {
    perror("No se pudo abrir el archivo Informacion/directorios.txt");
    return EXIT_FAILURE;
  }

  if ( ! (archivos = fopen("Informacion/archivos.txt", "w")) ) {
    perror("No se pudo abrir el archivo Informacion/archivos.txt");
    return EXIT_FAILURE;
  }

  /* 3. Imprimir el UID y PID en los archivos */
  imprimidor(recorrido,   "Id_usuario: %d Id_programa: %d", getuid(), getpid());
  imprimidor(directorios, "Id_usuario: %d Id_programa: %d", getuid(), getpid());
  imprimidor(archivos,    "Id_usuario: %d Id_programa: %d", getuid(), getpid());

  /* 4. Segun los argumentos entregados por el usuario, ejecutar el recorrido acorde al path entregado */
  switch (argc) {
    case 1:  recorrer(".", ".", 0);            break;
    case 2:  recorrer(argv[1], argv[1], 0);    break;
    default: perror("Argumentos invalidos\n"); return EXIT_FAILURE;
  }

  /* 5. Cerrar los archivos y terminar la ejecucion */
  fclose(recorrido);
  fclose(directorios);
  fclose(archivos);

  return EXIT_SUCCESS;
}

/**
 * Genera una lista de directorios (directory) y una lista de los archivos (file)
 * presentes en el path actual. Luego para cada directorio se recorre recursivamente
 * el arbol de directorios. En cada ejecucion se escribe en los archivos de salida
 * los datos pedidos (permisos, ubicacion, forma de recorrer, conteo de archivos)
 *
 * @param path               es el path que se esta visitando actualmente (cada paso recursivo se
 *                           agrega /carpeta_nueva al path)
 * @param current_directory  es el nombre del directorio actual que se esta analizando (la
 *                           ultima parte del path: ej. /Users/me/tarea/A1,  A1 seria
 *                           el current_directory)
 * @param indent             es el nivel de indentacion que se debe aplicar dependiendo de la
 *                           profundidad de la recursion (en cada iteracion se suma 1 a la indentacion)
 */
void recorrer(const char path[MAXPATHLEN], const char current_directory[MAXPATHLEN], int indent) {
  int    i;
  int    number_directories;
  int    number_files;
  struct dirent **directory;
  struct dirent **file;
  char   next_directory[MAXPATHLEN];
  char   current_file[MAXPATHLEN];

  number_directories = scandir(path, &directory, filter_directories, alphasort);
  number_files       = scandir(path, &file,      filter_files,       alphasort);

  if (number_directories >= 0) {
    /* 1. Imprimir a directorios.txt */
    imprimidor(directorios, "\n%*.s", indent, " ");
    imprimidor(directorios, "Directorio %s contiene: %d Carpetas y %d Archivos", current_directory, number_directories, number_files);

    /* 2. Imprimir a archivos.txt los archivos con su ubicacion y permisos */
    for(i = 0; i < number_files; i++) {
      imprimidor(archivos, "\n%s ubicado en %s tiene permisos de: ", file[i]->d_name, current_directory);
      sprintf(current_file, "%s/%s", path, file[i]->d_name);
      if ( access(current_file, R_OK) == 0 ) imprimidor(archivos, "Lectura, ");
      if ( access(current_file, W_OK) == 0 ) imprimidor(archivos, "Escritura, ");
      if ( access(current_file, X_OK) == 0 ) imprimidor(archivos, "Ejecucion");
      free(file[i]);
    }

    /* 3. Imprimir a recorrido.txt la carpeta actual con si nivel de indentacion*/
    for (i = 0; i < number_directories; i++) {
      imprimidor(recorrido, "\n%s", directory[i]->d_name);
      sprintf(next_directory, "%s/%s", path, directory[i]->d_name);  // Forma el path incluyendo el directorio nuevo path = path/dir_nuevo
      recorrer(next_directory, directory[i]->d_name, indent + 4);
      free(directory[i]);
    }
    free(directory);
    free(file);
  }else {
    perror("Couldn't open the directory");
  }
}
