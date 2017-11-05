#include <stdio.h>
#include "cons.h"
#include "cons_list.h"
#include "interpret.h"
#include "prelude.h"

void test(void);

int main(int n, char *args[n]) {
    Cons *cons;

    if (n == 1) {
        test();
    } else if (n == 2) {
        cons = interpret(cons_from_string(args[1])).value;

        printf("%s\n", cons_to_string(cons));
    }

    return 0;
}

void test(void) {
    cons_test();
    interpret_test();
    prelude_test();
    cons_list_test();

    printf("All tests pass :)\n");
}
