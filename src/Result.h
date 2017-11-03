#ifndef RESULT_H
#define RESULT_H

typedef struct _Result Result;

Result Result_invalid(void);
Result Result_valid(Cons *value);

#endif
