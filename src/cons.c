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

Cons *from_string(char *s) {
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
