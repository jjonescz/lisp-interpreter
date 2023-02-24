# lisp_interpreter

This program interprets a simple dialect of the LISP language similar to Scheme.

## Building the code

### Windows

Just open the `.sln` file in Visual Studio 2017 or execute:

```ps1
msbuild .\LispInterpreter.sln /p:Configuration=Release
```

### Unix

```bash
g++ --std=c++14 src/lisp_interpreter/*.cpp -o lisp_interpreter
```

## Things to note about the language

All compile-time expressions and run-time values are just of two kinds: *pairs* and *tokens*.

Pair simply contains two other expressions.
Token can be an integer (32-bit), decimal number (`double`), string or special value (lambda or internal function).
*Proper list* is a chain of pairs ended with *nil token* (that is just a regular string token written as `()`).

Token names are case-sensitive (and hence the whole language is case-sensitive).

The program supports classic syntax for lists and dotted pairs. If we write `(a b c)`, that produces a proper list and is equivalent to writing `(a . (b . (c . ())))`.

Quotation syntactic sugar is also supported. That is, writing `'x` is equivalent to writing `(quote x)`.

Function applications are *strictly evaluated* for user defined functions (lambdas), but that may not be true for some internal functions.

These primitive (internal) functions are defined by default and have their classic behavior: `quote`, `car`, `cdr`, `cons`, `list`, `lambda`, `define`, `set!`, `pair?`, `eq?`, `if`, `eval`, `+`, `-`, `*`, `/`. If these functions return a truth value, it is represented by token `#t` or `()` for "true" or "false", respectively. `if` considers everything but `()` to be truthful.

Variables have *lexical scope* which is achieved classically by environments.

## Limitations

Operations with numbers can overflow and no error is reported when that happens.

`define` currently supports only variables, not functions. So, functions have to be defined using lambas, e.g. `(define add (lambda (x y) (+ x y)))`.

## Using the program

The program is a simple interpreter that accepts commands on the standard input, parses them, evaluates them and prints the results or an error.

There can be multiple expressions on a single line, in which case all of them are evaluated and results are printed on separate lines. On the other hand, there can be unfinished expressions typed in and the program won't evaluate them unless they are finished (the interpreter considers expression finished if it has equal number of opening and closing brackets).

Every parsed expression is actually passed to the current global environment's `eval` function. That is a normal evaluator by default, but it can be redefined to behave differently (effectively changing the language's behavior at runtime).

## Examples

In the following examples, interesting output of the interpreter is written as a comment (a line starting with `;`).

### Mapping over lists

```scheme
(define map (lambda (proc items)
  (if (pair? items)
    (cons (proc (car items))
      (map proc (cdr items)))
    ())))
(map (lambda (x) (+ x 1)) '(1 2 3))
; (2 3 4)
```

### Redefining `eval`

```scheme
(define old-eval eval)
(define ans ()) ; this slot will hold result of each expression evaluated
(define eval (lambda (x)
  (set! ans (old-eval x))))
(+ 1 2)
; 3
ans
; 3
```
