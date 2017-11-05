#ifndef PRELUDE_H
#define PRELUDE_H

#include "cons.h"

Cons *prelude_add(Cons *cons_a, Cons *cons_b);
Cons *prelude_minus(Cons *cons_a, Cons *cons_b);
Cons *prelude_multiply(Cons *cons_a, Cons *cons_b);
Cons *prelude_equal(Cons *cons_a, Cons *cons_b);
Cons *prelude_if(Cons *cond, Cons *cons_a, Cons *cons_b);
Cons *prelude_id(Cons *cons);
void prelude_test(void);

#endif
