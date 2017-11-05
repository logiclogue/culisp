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
    int line_size = 1024;
    char *line = malloc(line_size);
    Result result;

    while (!feof(stdin)) {
        printf("culisp> ");
        
        fgets(line, line_size, stdin);

        result = interpret(cons_from_string(line));

        if (result.valid) {
            printf("%s\n", cons_to_string(result.value));
        } else {
            printf("Invalid input\n");
        }
    }
}

void test(void) {
    cons_test();
    cons_list_test();
    interpret_test();
    prelude_test();

    printf("All tests pass :)\n");
}
