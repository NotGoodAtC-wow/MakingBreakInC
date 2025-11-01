#include <assert.h>
#include <math.h>
#include "convert.h"

static int almost_eq(double a, double b) { return fabs(a - b) < 1e-9; }

int main(void) {
    bool ok = true;

    // Температура
    assert(almost_eq(convert_temp(100, "C", "K", &ok), 373.15) && ok);
    assert(almost_eq(convert_temp(32,  "F", "C", &ok), 0.0) && ok);

    // Длина
    assert(almost_eq(convert_length(1, "km", "m", &ok), 1000.0) && ok);
    assert(almost_eq(convert_length(2.54, "cm", "in", &ok), 1.0) && ok);

    // Ошибки (должны ставить ok = false)
    ok = true; (void)convert_length(1, "xx", "m", &ok);  assert(!ok);
    ok = true; (void)convert_temp(0, "C", "XX", &ok);    assert(!ok);

    return 0;
}
