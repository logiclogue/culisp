#include <assert.h>
#include "cons_list.h"

Cons *cons_list_item(int n, Cons *cons) {
    if (cons_is_empty(cons)) {
        return cons_empty();
    } else if (n == 0 && cons_is_white_space(cons->car)) {
        return cons_empty();
    } else if (n == 0) {
        return cons_new(cons->car, cons_list_item(n, cons->cdr));
    } else if (cons_is_white_space(cons->car)
            && cons_is_white_space(cons->cdr->car)) {
        return cons_list_item(n, cons->cdr);
    } else if (cons_is_white_space(cons->car)) {
        return cons_list_item(n - 1, cons->cdr);
    }

    return cons_list_item(n, cons->cdr);
}

void cons_list_test(void) {
    Cons *list = cons_from_string("one  two three");

    assert(cons_equal(
        cons_list_item(1, list),
        cons_from_string("two")));
    assert(cons_equal(
        cons_list_item(1, cons_from_string("")),
        cons_from_string("")));
}
