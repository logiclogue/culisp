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

Cons *prelude_equal(Cons *cons_a, Cons *cons_b) {
    return cons_from_bool(cons_equal(cons_a, cons_b));
}

Cons *prelude_if(Cons *cond, Cons *cons_a, Cons *cons_b) {
    if (cons_to_bool(cond)) {
        return cons_a;
    }

    return cons_b;
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
    assert(cons_equal(
        prelude_equal(cons_from_int(2), cons_from_int(2)),
        cons_from_string("#t")));
    assert(cons_equal(
        prelude_equal(cons_from_int(1), cons_from_int(2)),
        cons_from_string("#f")));
    assert(cons_equal(
        prelude_if(cons_from_bool(true), cons_from_int(1), cons_from_int(2)),
        cons_from_int(1)));
    assert(cons_equal(
        prelude_if(cons_from_bool(false), cons_from_int(1), cons_from_int(2)),
        cons_from_int(2)));
}
