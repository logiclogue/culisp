#include "cons.h"

struct _Cons {
    char car;
    Cons *cdr;
};
