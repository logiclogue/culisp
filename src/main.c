#include <stdio.h>
#include <stdlib.h>
#include "cons.h"
#include "cons_list.h"
#include "interpret.h"
#include "prelude.h"

void test(void);
void repl(void);

int main(int n, char *args[n]) {
    Cons *cons;

    if (n == 1) {
        repl();
    } else if (n == 2
        && cons_equal(
            cons_from_string(args[1]),
            cons_from_string("test"))) {
        test();
    } else if (n == 2) {
        cons = interpret(cons_from_string(args[1])).value;

        printf("%s\n", cons_to_string(cons));
    }

    return 0;
}

void repl(void) {
    Cons *cons = cons_empty();
    char current_char;

    printf("culisp> ");

    while (current_char != '\n') {
        current_char = fgetc(stdin);

        cons = cons_add(cons, cons_new(current_char, cons_empty()));
    }

    Result result = interpret(cons);

    if (result.valid) {
        printf("%s\n", cons_to_string(result.value));
    } else {
        printf("Invalid input\n");
    }

    repl();
}

void test(void) {
    cons_test();
    cons_list_test();
    interpret_test();
    prelude_test();

    printf("All tests pass :)\n");
}
