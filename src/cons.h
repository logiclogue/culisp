#ifndef CONS_H
#define CONS_H

#include <stdbool.h>

typedef struct _Cons Cons;

Cons *cons_new(char value, Cons *cons);
Cons *cons_from_string(char *s);
void destroy_cons(Cons *cons);
char cons_head(Cons *cons);
Cons *cons_tail(Cons *cons);
char cons_item(int i, Cons *cons);
char cons_last(Cons *cons);
Cons *cons_init(Cons *cons);
Cons *cons_take(int n, Cons *cons);
//Cons *cons_drop(int n, Cons *cons);
int cons_length(Cons *cons);
//Cons *cons_add(Cons *cons_a, Cons *cons_b);
//bool cons_equal(Cons *cons_a, Cons *cons_b);
//Cons *cons_map(char (*f)(char c), Cons *cons);
//Cons *cons_trim(Cons *cons);
//bool cons_is_white_space(char c);
void cons_test(void);

#endif
