# CuLisp

A lisp-like expression evaluator.

## Background

This started as a project where I wanted to write my own Lisp-like language. So
far it's only able to evaluate simple expressions.

## Building

- Run `make`

## Usage

Typing `./build/culisp` will spawn a REPL as shown below:

`culisp> `

To run the tests type `./build/culisp test`

## Examples

Adding two numbers together

`(add 1 2)`

Nesting function calls

`(add (minus 10 5) 5)`

If statement

`(if (equal 1 2) (add 1 2) (minus 1 2))`

If statement returning function name

`((if (equal 1 1) add minus) 100 10)`

## Functions

- `(add <int> <int>)` returns `<int>`
- `(minus <int> <int>)` returns `<int>`
- `(multiply <int> <int>)` returns `<int>`
- `(equal <a> <a>)` returns `<bool>`
- `(if <bool> <a> <a>)` returns `<a>`
- `(id <a>)` returns `<a>`

## Issues

- The program is incredibly prone to memory leaks
- CuLisp isn't actually a complete language since variables and functions can't be defined

## Author

Jordan Lord
