#ifndef INTERPRET_H
#define INTERPRET_H

#include "Result.h"
#include "cons.h"

Result interpret(Cons *cons);
Result interpret_number(Cons *cons);
Result interpret_name(Cons *cons);
Result interpret_function(Cons *cons);
Result interpret_bool(Cons *cons);
void interpret_test(void);

#endif
