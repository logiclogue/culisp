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
    Result result;
    Cons *previous_cons;
    char current_char;
    bool is_new_line = false;

    printf("culisp> ");

    while (!is_new_line) {
        current_char = fgetc(stdin);

        if (current_char == '\n') {
            is_new_line = true;
        } else {
            printf("%c\n", fgetc(stdin));
        }
    }

    printf("ENDEDN\n");

    //while (!feof(stdin)) {
    //    printf("culisp> ");
    //    
    //    fgets(line, line_size, stdin);
    //    printf("HERE\n");

    //    result = interpret(cons_from_string(line));

    //    if (result.valid) {
    //        printf("%s\n", cons_to_string(result.value));
    //    } else {
    //        printf("Invalid input\n");
    //    }
    //}
}

void test(void) {
    cons_test();
    cons_list_test();
    interpret_test();
    prelude_test();

    printf("All tests pass :)\n");
}
