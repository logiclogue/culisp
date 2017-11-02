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

void cons_test(void) {
    Cons *jordan = cons_from_string("Jordan");

    assert(cons_head(jordan) == 'J');
    assert(cons_head(cons_tail(jordan)) == 'o');
}
