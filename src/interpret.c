#include <assert.h>
#include <stdbool.h>
#include "Result.h"
#include "cons.h"
#include "interpret.h"

static bool is_digit(char value) {
    return value >= '0' && value <= '9';
}

Result interpret_number(Cons *cons) {
    return Result_invalid();
}

void interpret_test(void) {
    assert(interpret_number(cons_from_string("123")).valid);
    assert(interpret_number(cons_from_string("-123")).valid);
    assert(!interpret_number(cons_from_string("a")).valid);
    assert(!interpret_number(cons_from_string("")).valid);
}
