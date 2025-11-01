#include "convert.h"
#include <ctype.h>
#include <string.h>

static double to_meters(double v, const char* u, bool* ok) {
    if (iequal(u, "m"))   return v;
    if (iequal(u, "cm"))  return v / 100.0;
    if (iequal(u, "mm"))  return v / 1000.0;
    if (iequal(u, "km"))  return v * 1000.0;
    if (iequal(u, "in"))  return v * 0.0254;
    if (iequal(u, "ft"))  return v * 0.3048;
    *ok = false; return 0.0;
}

static double from_meters(double m, const char* u, bool* ok) {
    if (iequal(u, "m"))   return m;
    if (iequal(u, "cm"))  return m * 100.0;
    if (iequal(u, "mm"))  return m * 1000.0;
    if (iequal(u, "km"))  return m / 1000.0;
    if (iequal(u, "in"))  return m / 0.0254;
    if (iequal(u, "ft"))  return m / 0.3048;
    *ok = false; return 0.0;
}

double convert_length(double v, const char* from, const char* to, bool* ok) {
    if (ok) *ok = true;
    double m = to_meters(v, from, ok);
    if (ok && !*ok) return 0.0;
    return from_meters(m, to, ok);
}

// Температура: C, F, K
double convert_temp(double v, const char* from, const char* to, bool* ok) {
    if (ok) *ok = true;
    double c;

    if (iequal(from, "C")) c = v;
    else if (iequal(from, "F")) c = (v - 32.0) * 5.0 / 9.0;
    else if (iequal(from, "K")) c = v - 273.15;
    else { if (ok) *ok = false; return 0.0; }

    if (iequal(to, "C")) return c;
    if (iequal(to, "F")) return c * 9.0 / 5.0 + 32.0;
    if (iequal(to, "K")) return c + 273.15;

    if (ok) *ok = false;
    return 0.0;
}

int iequal(const char* a, const char* b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        ++a; ++b;
    }
    return *a == '\0' && *b == '\0';
}
