#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cons.h"

struct _Cons {
    char car;
    Cons *cdr;
};

Cons *cons_new(char value, Cons *cons) {
    Cons *self = malloc(sizeof(Cons));

    self->car = value;
    self->cdr = cons;

    return self;
}

Cons *cons_from_string(char *s) {
    Cons *string = NULL;
    Cons *previous_char = NULL;
    Cons *current_char = NULL;

    for (int i = 0; s[i] != '\0'; i += 1) {
        current_char = cons_new(s[i], NULL);

        if (string == NULL) {
            string = current_char;
        }

        if (previous_char != NULL) {
            previous_char->cdr = current_char;
        }

        previous_char = current_char;
    }

    return string;
}

void destroy_cons(Cons *cons) {
    if (cons == NULL) {
        return;
    }

    destroy_cons(cons->cdr);
    free(cons);
}

char cons_head(Cons *cons) {
    if (cons == NULL) {
        return '\0';
    }

    return cons->car;
}

Cons *cons_tail(Cons *cons) {
    if (cons == NULL) {
        return NULL;
    }

    return cons->cdr;
}

char cons_item(int i, Cons *cons) {
    if (cons == NULL) {
        return '\0';
    } else if (i == 0) {
        return cons->car;
    }

    return cons_item(i - 1, cons->cdr);
}

char cons_last(Cons *cons) {
    if (cons == NULL) {
        return '\0';
    } else if (cons->cdr == NULL) {
        return cons->car;
    }

    return cons_last(cons->cdr);
}

int cons_length(Cons *cons) {
    if (cons == NULL) {
        return 0;
    }

    return 1 + cons_length(cons->cdr);
}

Cons *cons_take(int n, Cons *cons) {
    if (n <= 0) {
        return NULL;
    } else if (cons->cdr == NULL) {
        return cons;
    }

    return cons_new(cons->car, cons_take(n - 1, cons->cdr));
}

Cons *cons_init(Cons *cons) {
    return cons_take(cons_length(cons) - 1, cons);
}

Cons *cons_drop(int n, Cons *cons) {
    if (cons == NULL || n == 0) {
        return cons;
    }

    return cons_drop(n - 1, cons->cdr);
}

bool cons_equal(Cons *cons_a, Cons *cons_b) {
    if (cons_a == NULL && cons_b == NULL) {
        return true;
    } else if (cons_a == NULL || cons_b == NULL) {
        return false;
    } else if (cons_a->car != cons_b->car) {
        return false;
    }

    return cons_equal(cons_a->cdr, cons_b->cdr);
}

Cons *cons_add(Cons *cons_a, Cons *cons_b) {
    if (cons_a == NULL) {
        return cons_b;
    }

    return cons_new(cons_a->car, cons_add(cons_a->cdr, cons_b));
}

Cons *cons_trim(Cons *cons) {
    if (cons == NULL) {
        return NULL;
    } else if (cons_is_white_space(cons->car)) {
        return cons_trim(cons->cdr);
    } else if (cons_is_white_space(cons_last(cons))) {
        return cons_trim(cons_init(cons));
    }

    return cons;
}

bool cons_is_white_space(char c) {
    return c == 9  || c == 10 ||
           c == 11 || c == 12 ||
           c == 13 || c == 32 ||
           c == 133 || c == 160;
}

void cons_test(void) {
    Cons *jordan = cons_from_string("Jordan");
    Cons *j = cons_from_string("J");

    assert(cons_head(jordan) == 'J');
    assert(cons_head(cons_tail(jordan)) == 'o');
    assert(cons_item(5, jordan) == 'n');
    assert(cons_item(20, jordan) == '\0');
    assert(cons_item(1, NULL) == '\0');
    assert(cons_last(NULL) == '\0');
    assert(cons_last(jordan) == 'n');
    assert(cons_last(cons_init(NULL)) == '\0');
    assert(cons_last(cons_init(j)) == '\0');
    assert(cons_last(cons_init(jordan)) == 'a');
    assert(cons_last(cons_take(3, jordan)) == 'r');
    assert(cons_length(jordan) == 6);
    assert(cons_head(cons_drop(1, jordan)) == 'o');
    assert(cons_drop(100, NULL) == NULL);
    assert(cons_equal(jordan, jordan));
    assert(!cons_equal(j, jordan));
    assert(cons_equal(NULL, NULL));
    assert(cons_equal(cons_add(j, cons_from_string("ordan")), jordan));
    assert(cons_equal(
        cons_trim(cons_from_string("  test  ")),
        cons_from_string("test")));
}
