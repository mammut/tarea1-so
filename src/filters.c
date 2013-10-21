#include <dirent.h>
#include <string.h>
#include "../include/filters.h"

/**
 * Filtro para la funcion scandir. Solo muestra los directorios
 *
 * @param  dir es el directorio que se esta filtrando
 **/
int filter_directories(const struct dirent *dir) {
  int is_hidden = (dir->d_name[0] == '.') || (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0);

  if (is_hidden && dir->d_type == DT_DIR)
    return 0;

  if (dir->d_type == DT_DIR)
    return 1;
  return 0;
}

/**
 * Filtro para la funcion scandir. Solo muestra los archivos (no directorios)
 *
 * @param  dir es el directorio que se esta filtrando
 **/
int filter_files(const struct dirent *dir) {
  if (dir->d_name[0] == '.' && dir->d_type != DT_DIR)
    return 0;

  if (dir->d_type != DT_DIR)
    return 1;
  return 0;
}