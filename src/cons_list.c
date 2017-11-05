#include <assert.h>
#include <stdbool.h>
#include "cons_list.h"

static Cons *_cons_list_item(int brackets, int n, Cons *cons) {
    if (cons_is_empty(cons)) {
        return cons_empty();
    }

    if (cons->car == '(') {
        brackets += 1;
    } else if (cons->car == ')') {
        brackets -= 1;
    }

    if (cons->car == '(' && brackets == 1) {
        return _cons_list_item(brackets, n, cons->cdr);
    } else if (brackets == 0) {
        return cons_empty();
    } else if (n == 0 && cons_is_white_space(cons->car) && brackets == 1) {
        return cons_empty();
    } else if (n == 0 && brackets >= 1) {
        return cons_new(
            cons->car,
            _cons_list_item(brackets, n, cons->cdr));
    } else if (cons_is_white_space(cons->car)
            && cons_is_white_space(cons->cdr->car)
            && brackets == 1) {
        return _cons_list_item(brackets, n, cons->cdr);
    } else if (cons_is_white_space(cons->car) && brackets == 1) {
        return _cons_list_item(brackets, n - 1, cons->cdr);
    }

    return _cons_list_item(brackets, n, cons->cdr);
}

Cons *cons_list_item(int n, Cons *cons) {
    return _cons_list_item(0, n, cons);
}

static int _cons_list_length(int n, Cons *cons) {
    if (cons_is_empty(cons_list_item(n, cons))) {
        return n;
    }

    return _cons_list_length(n + 1, cons);
}

int cons_list_length(Cons *cons) {
    return _cons_list_length(0, cons);
}

void cons_list_test(void) {
    Cons *list = cons_from_string("(one  two three)");
    Cons *empty_list = cons_from_string("");
    Cons *nested_list = cons_from_string("(one (two three) four)");

    assert(cons_equal(
        cons_list_item(0, list),
        cons_from_string("one")));
    assert(cons_equal(
        cons_list_item(1, list),
        cons_from_string("two")));
    assert(cons_equal(
        cons_list_item(1, empty_list),
        cons_from_string("")));
    assert(cons_equal(
        cons_list_item(1, nested_list),
        cons_from_string("(two three)")));
    assert(cons_equal(
        cons_list_item(2, nested_list),
        cons_from_string("four")));
    assert(cons_list_length(list) == 3);
    assert(cons_list_length(empty_list) == 0);
    assert(cons_list_length(nested_list) == 3);
}
