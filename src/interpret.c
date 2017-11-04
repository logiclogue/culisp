#include <assert.h>
#include <stdbool.h>
#include "Result.h"
#include "cons.h"
#include "interpret.h"

static bool is_digit(char value) {
    return value >= '0' && value <= '9';
}

Result interpret_number(Cons *cons) {
    if (cons_is_empty(cons)) {
        return Result_invalid();
    } else if (cons->car == '-' && cons_all(is_digit, cons->cdr)) {
        return Result_valid(cons);
    } else if (cons_all(is_digit, cons)) {
        return Result_valid(cons);
    }

    return Result_invalid();
}

static bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

Result interpret_name(Cons *cons) {
    if (cons_is_empty(cons)) {
        return Result_invalid();
    } else if (cons_all(is_alpha, cons)) {
        return Result_valid(cons);
    }

    return Result_invalid();
}

void interpret_test(void) {
    assert(interpret_number(cons_from_string("123")).valid);
    assert(interpret_number(cons_from_string("-123")).valid);
    assert(!interpret_number(cons_from_string("a")).valid);
    assert(!interpret_number(cons_from_string("")).valid);
    assert(interpret_name(cons_from_string("jordan")).valid);
    assert(interpret_name(cons_from_string("JORDAN")).valid);
    assert(!interpret_name(cons_from_string("j0rdan")).valid);
    assert(!interpret_name(cons_from_string("")).valid);
}
