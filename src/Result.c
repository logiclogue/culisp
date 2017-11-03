#include <stdbool.h>
#include <stdlib.h>
#include "cons.h"
#include "Result.h"

struct _Result {
    bool valid;
    Cons *value;
};

Result Result_invalid(void) {
    return (Result) { false, NULL };
}

Result Result_valid(Cons *value) {
    return (Result) { true, value };
}
