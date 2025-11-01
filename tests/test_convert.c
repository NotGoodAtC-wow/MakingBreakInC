#include <assert.h>
#include <math.h>
#include "convert.h"

static int almost_eq(double a, double b) { return fabs(a - b) < 1e-9; }

int main(void) {
    bool ok = true;
    assert(almost_eq(convert_temp(0,   "C", "F", &ok), 32.0) && ok);
    assert(almost_eq(convert_temp(273.15, "K", "C", &ok), 0.0) && ok);
    assert(almost_eq(convert_length(1, "m", "cm", &ok), 100.0) && ok);
    assert(almost_eq(convert_length(2.54, "cm", "in", &ok), 1.0) && ok);
    return 0;
}
