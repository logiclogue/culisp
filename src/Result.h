#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>
#include "cons.h"

typedef struct _Result Result;

struct _Result {
    bool valid;
    Cons *value;
};

Result Result_invalid(void);
Result Result_valid(Cons *value);

#endif
