#include <stdio.h>
#include "cons.h"
#include "interpret.h"

void test(void);

int main(void) {
    test();

    return 0;
}

void test(void) {
    cons_test();
    interpret_test();

    printf("All tests pass :)\n");
}
