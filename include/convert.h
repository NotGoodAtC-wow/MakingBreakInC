#ifndef CONVERT_H
#define CONVERT_H

#include <stdbool.h>

double convert_temp(double v, const char* from, const char* to, bool* ok);
double convert_length(double v, const char* from, const char* to, bool* ok);
int iequal(const char* a, const char* b); // регистронезависимое сравнение

#endif
// header convertor, do not just refactor