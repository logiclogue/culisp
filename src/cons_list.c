#include <assert.h>
#include "cons_list.h"

Cons *cons_list(int n, Cons *cons) {
    if (cons_is_empty(cons)) {
        return cons_empty();
    } else if (n == 0 && cons_is_white_space(cons->car)) {
        return cons_empty();
    } else if (n == 0) {
        return cons_new(cons->car, cons_list(n, cons->cdr));
    } else if (cons_is_white_space(cons->car)
            && cons_is_white_space(cons->cdr->car)) {
        return cons_list(n, cons->cdr);
    } else if (cons_is_white_space(cons->car)) {
        return cons_list(n - 1, cons->cdr);
    }

    return cons_list(n, cons->cdr);
}

void cons_list_test(void) {
    assert(cons_equal(
        cons_list(1, cons_from_string("one  two three")),
        cons_from_string("two")));
    assert(cons_equal(
        cons_list(1, cons_from_string("")),
        cons_from_string("")));
}
