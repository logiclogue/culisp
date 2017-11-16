#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "Result.h"
#include "cons.h"
#include "cons_list.h"
#include "interpret.h"
#include "prelude.h"

static bool is_digit(char value) {
    return value >= '0' && value <= '9';
}

Result interpret(Cons *cons) {
    if (cons_is_empty(cons)) {
        return Result_invalid();
    }

    Result number_result = interpret_number(cons);
    
    if (number_result.valid) {
        return number_result;
    }

    Result bool_result = interpret_bool(cons);
    
    if (bool_result.valid) {
        return bool_result;
    }

    Result name_result = interpret_name(cons);
    
    if (name_result.valid) {
        return name_result;
    }
    
    Result function_result = interpret_function(cons);
    
    if (function_result.valid) {
        return function_result;
    }

    return Result_invalid();
}

Result interpret_number(Cons *cons) {
    if (cons_is_empty(cons)) {
        return Result_invalid();
    } else if (cons->car == '-' && cons_all(is_digit, cons->cdr)) {
        return Result_valid(cons);
    } else if (cons_all(is_digit, cons)) {
        return Result_valid(cons);
    }

    return Result_invalid();
}

static bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

Result interpret_name(Cons *cons) {
    if (cons_is_empty(cons)) {
        return Result_invalid();
    } else if (cons_all(is_alpha, cons)) {
        return Result_valid(cons);
    }

    return Result_invalid();
}

Result interpret_bool(Cons *cons) {
    if (cons_is_empty(cons)) {
        return Result_invalid();
    } else if (cons_length(cons) != 2) {
        return Result_invalid();
    } else if (cons->car == '#'
               && (cons->cdr->car == 't' || cons->cdr->car == 'f')) {
        return Result_valid(cons);
    }

    return Result_invalid();
}

Result interpret_function(Cons *cons) {
    Result command = interpret(cons_list_item(0, cons));
    Result first_param = interpret(cons_list_item(1, cons));
    Result second_param = interpret(cons_list_item(2, cons));
    Result third_param = interpret(cons_list_item(3, cons));
    int length = cons_list_length(cons);

    if (!command.valid) {
        return Result_invalid();
    }

    if (cons_equal(command.value, cons_from_string("add"))
        && first_param.valid
        && second_param.valid
        && length == 3) {
        return Result_valid(prelude_add(
            first_param.value,
            second_param.value));
    } else if (cons_equal(command.value, cons_from_string("minus"))
        && first_param.valid
        && second_param.valid
        && length == 3) {
        return Result_valid(prelude_minus(
            first_param.value,
            second_param.value));
    } else if (cons_equal(command.value, cons_from_string("id"))
        && first_param.valid
        && length == 2) {
        return Result_valid(prelude_id(
            first_param.value));
    } else if (cons_equal(command.value, cons_from_string("multiply"))
        && first_param.valid
        && second_param.valid
        && length == 3) {
        return Result_valid(prelude_multiply(
            first_param.value,
            second_param.value));
    } else if (cons_equal(command.value, cons_from_string("equal"))
        && first_param.valid
        && second_param.valid
        && length == 3) {
        return Result_valid(prelude_equal(
            first_param.value,
            second_param.value));
    } else if (cons_equal(command.value, cons_from_string("if"))
        && first_param.valid && second_param.valid && third_param.valid
        && length == 4) {
        return Result_valid(prelude_if(
            first_param.value,
            second_param.value,
            third_param.value));
    } else if (cons_equal(command.value, cons_from_string("eval"))
        && first_param.valid
        && length == 2) {
        return Result_valid(prelude_eval(first_param.value));
    }

    return Result_invalid();
}

void interpret_test(void) {
    assert(interpret_number(cons_from_string("123")).valid);
    assert(interpret_number(cons_from_string("-123")).valid);
    assert(!interpret_number(cons_from_string("a")).valid);
    assert(!interpret_number(cons_from_string("")).valid);
    assert(interpret_name(cons_from_string("jordan")).valid);
    assert(interpret_name(cons_from_string("JORDAN")).valid);
    assert(!interpret_name(cons_from_string("j0rdan")).valid);
    assert(!interpret_name(cons_from_string("")).valid);
    assert(!interpret(cons_from_string("")).valid);
    assert(interpret(cons_from_string("123")).valid);
    assert(interpret(cons_from_string("jordan")).valid);
    assert(!interpret_function(cons_from_string("add 1 2")).valid);
    assert(interpret_function(cons_from_string("(add 1 2)")).valid);
    assert(cons_equal(
        interpret_function(cons_from_string("(add 1 2)")).value,
        cons_from_string("3")));
    assert(cons_equal(
        interpret(cons_from_string("(add 1 2)")).value,
        cons_from_string("3")));
    assert(cons_equal(
        interpret(cons_from_string("(add (add 10 10) 10)")).value,
        cons_from_int(30)));
    assert(interpret(cons_from_string("(id add)")).valid);
    assert(interpret(cons_from_string("#t")).valid);
    assert(interpret(cons_from_string("#f")).valid);
}
