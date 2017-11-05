#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cons.h"

Cons *cons_new(char value, Cons *cons) {
    Cons *self = malloc(sizeof(Cons));

    static int total = 0;

    total += 1;

    self->car = value;
    self->cdr = cons;

    return self;
}

Cons *cons_empty(void) {
    return NULL;
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

Cons *cons_from_int(int i) {
    char *output = malloc(sizeof(char) * 100);

    sprintf(output, "%d", i);

    Cons *cons = cons_from_string(output);

    free(output);

    return cons;
}

void destroy_cons(Cons *cons) {
    if (cons_is_empty(cons)) {
        return;
    }

    static int total = 0;

    total += 1;

    destroy_cons(cons->cdr);
    free(cons);
}

char *cons_to_string(Cons *cons) {
    int len = cons_length(cons);
    char *string = malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i += 1) {
        string[i] = cons_item(i, cons);
    }

    string[len] = '\0';

    return string;
}

int cons_to_int(Cons *cons) {
    char *string = cons_to_string(cons);

    int value = atoi(string);

    free(string);

    return value;
}

char cons_head(Cons *cons) {
    if (cons_is_empty(cons)) {
        return '\0';
    }

    return cons->car;
}

Cons *cons_tail(Cons *cons) {
    if (cons_is_empty(cons)) {
        return cons_empty();
    }

    return cons->cdr;
}

char cons_item(int i, Cons *cons) {
    if (cons_is_empty(cons)) {
        return '\0';
    } else if (i == 0) {
        return cons->car;
    }

    return cons_item(i - 1, cons->cdr);
}

char cons_last(Cons *cons) {
    if (cons_is_empty(cons)) {
        return '\0';
    } else if (cons_is_empty(cons->cdr)) {
        return cons->car;
    }

    return cons_last(cons->cdr);
}

int cons_length(Cons *cons) {
    if (cons_is_empty(cons)) {
        return 0;
    }

    return 1 + cons_length(cons->cdr);
}

Cons *cons_take(int n, Cons *cons) {
    if (n <= 0) {
        return cons_empty();
    } else if (cons_is_empty(cons->cdr)) {
        return cons;
    }

    return cons_new(cons->car, cons_take(n - 1, cons->cdr));
}

Cons *cons_init(Cons *cons) {
    return cons_take(cons_length(cons) - 1, cons);
}

Cons *cons_drop(int n, Cons *cons) {
    if (cons_is_empty(cons) || n == 0) {
        return cons;
    }

    return cons_drop(n - 1, cons->cdr);
}

bool cons_equal(Cons *cons_a, Cons *cons_b) {
    if (cons_is_empty(cons_a) && cons_is_empty(cons_b)) {
        return true;
    } else if (cons_is_empty(cons_a) || cons_is_empty(cons_b)) {
        return false;
    } else if (cons_a->car != cons_b->car) {
        return false;
    }

    return cons_equal(cons_a->cdr, cons_b->cdr);
}

Cons *cons_add(Cons *cons_a, Cons *cons_b) {
    if (cons_is_empty(cons_a)) {
        return cons_b;
    }

    return cons_new(cons_a->car, cons_add(cons_a->cdr, cons_b));
}

Cons *cons_trim(Cons *cons) {
    if (cons_is_empty(cons)) {
        return cons_empty();
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

bool cons_is_empty(Cons *cons) {
    return cons == NULL;
}

bool cons_is_last(Cons *cons) {
    if (cons_is_empty(cons)) {
        return false;
    } else if (cons_is_empty(cons->cdr)) {
        return true;
    }

    return false;
}

bool cons_all(bool (*f)(char c), Cons *cons) {
    if (cons_is_empty(cons)) {
        return false;
    } else if (cons_is_last(cons)) {
        return f(cons->car);
    } else if (!f(cons->car)) {
        return false;
    }

    return cons_all(f, cons->cdr);
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
    assert(cons_is_empty(cons_from_string("")));
    assert(!cons_is_empty(cons_from_string("test")));
    assert(!cons_is_last(cons_from_string("")));
    assert(cons_is_last(cons_from_string("a")));
    assert(!cons_is_last(cons_from_string("as")));
    assert(cons_all(cons_is_white_space, cons_from_string("   ")));
    assert(!cons_all(cons_is_white_space, cons_from_string(" a ")));
    assert(cons_to_int(cons_from_string("123")) == 123);
    assert(cons_equal(cons_from_int(123), cons_from_string("123")));
}
