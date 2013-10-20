#ifndef _FILTERS_H_INCLUDED_
#define _FILTERS_H_INCLUDED_

#define SHOW_HIDDEN_FILES 0   /* 0: no considera archivos ocultos, 1: si los considera */

int filter_files(const struct dirent *dir);
int filter_directories(const struct dirent *dir);

#endif