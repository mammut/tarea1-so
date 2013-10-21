#ifndef _FILTERS_H_INCLUDED_
#define _FILTERS_H_INCLUDED_

int filter_files(const struct dirent *dir);
int filter_directories(const struct dirent *dir);

#endif