#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "Result.h"
#include "cons.h"
#include "interpret.h"
#include "prelude.h"

static bool is_digit(char value) {
    return value >= '0' && value <= '9';
}

Result interpret(Cons *cons) {
    if (interpret_number(cons).valid) {
        return interpret_number(cons);
    } else if (interpret_name(cons).valid) {
        return interpret_name(cons);
    }

    return Result_invalid();
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

Result interpret_function(Cons *cons) {
    Cons *without_brackets = cons_tail(cons_init(cons));
    Cons *with_brackets = cons_add(
        cons_add(cons_from_string("("),
        without_brackets),
        cons_from_string(")"));

    if (!cons_equal(cons, with_brackets)) {
        return Result_invalid();
    }

    if (cons_equal(cons_list(0, without_brackets), cons_from_string("add"))) {
        return Result_valid(prelude_add(cons_list(1, without_brackets), cons_list(2, without_brackets)));
    };

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
    assert(!interpret(cons_from_string("")).valid);
    assert(interpret(cons_from_string("123")).valid);
    assert(interpret(cons_from_string("jordan")).valid);
    assert(!interpret_function(cons_from_string("add 1 2")).valid);
    assert(interpret_function(cons_from_string("(add 1 2)")).valid);
    assert(cons_equal(
        interpret_function(cons_from_string("(add 1 2)")).value,
        cons_from_string("3")));
}
