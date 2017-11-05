#include <assert.h>
#include "prelude.h"
#include "cons.h"

Cons *prelude_add(Cons *cons_a, Cons *cons_b) {
    int int_a = cons_to_int(cons_a);
    int int_b = cons_to_int(cons_b);

    return cons_from_int(int_a + int_b);
}

Cons *prelude_minus(Cons *cons_a, Cons *cons_b) {
    int int_a = cons_to_int(cons_a);
    int int_b = cons_to_int(cons_b);

    return cons_from_int(int_a - int_b);
}

Cons *prelude_id(Cons *cons) {
    return cons;
}

Cons *prelude_multiply(Cons *cons_a, Cons *cons_b) {
    int int_a = cons_to_int(cons_a);
    int int_b = cons_to_int(cons_b);

    return cons_from_int(int_a * int_b);
}

void prelude_test(void) {
    assert(cons_equal(
        prelude_add(cons_from_int(2), cons_from_int(3)),
        cons_from_int(5)));
    assert(cons_equal(
        prelude_minus(cons_from_int(2), cons_from_int(3)),
        cons_from_int(-1)));
    assert(cons_equal(
        prelude_id(cons_from_string("add")),
        cons_from_string("add")));
    assert(cons_equal(
        prelude_multiply(cons_from_int(2), cons_from_int(3)),
        cons_from_int(6)));
}
