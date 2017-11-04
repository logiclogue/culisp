#ifndef INTERPRET_H
#define INTERPRET_H

#include "Result.h"
#include "cons.h"

Result interpret_number(Cons *cons);
Result interpret_name(Cons *cons);
void interpret_test(void);

#endif
