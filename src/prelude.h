#ifndef PRELUDE_H
#define PRELUDE_H

#include "cons.h"

Cons *prelude_add(Cons *cons_a, Cons *cons_b);
Cons *prelude_minus(Cons *cons_a, Cons *cons_b);
void prelude_test(void);

#endif
