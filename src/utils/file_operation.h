#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <stdio.h>
#include <stdbool.h>

FILE *open_file(const char *);

size_t count_records(FILE *);
size_t count_fields(FILE *);

#endif