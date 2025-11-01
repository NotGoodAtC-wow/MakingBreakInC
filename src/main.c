#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

static void usage(void) {
    puts("Usage:");
    puts("  units-cli len <value> <from> <to>   (units: mm cm m km in ft)");
    puts("  units-cli temp <value> <from> <to>  (units: C F K)");
    puts("Examples:");
    puts("  units-cli len 10 cm in");
    puts("  units-cli temp 25 C F");
}

int main(int argc, char* argv[]) {
    if (argc != 5) { usage(); return 1; }

    const char* mode = argv[1];
    char* endptr = NULL;
    double value = strtod(argv[2], &endptr);
    if (endptr == argv[2]) { fprintf(stderr, "Bad number: %s\n", argv[2]); return 2; }

    const char* from = argv[3];
    const char* to   = argv[4];

    bool ok = true;
    double res = 0.0;

    if (iequal(mode, "len")) {
        res = convert_length(value, from, to, &ok);
    } else if (iequal(mode, "temp")) {
        res = convert_temp(value, from, to, &ok);
    } else {
        usage(); return 1;
    }

    if (!ok) { fprintf(stderr, "Unknown unit\n"); return 3; }

    printf("%.10g\n", res);
    return 0;
}
