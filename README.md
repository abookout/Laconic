# Laconic

Laconic is a programming language which has existed and evolved in my head since
I became interested in programming languages a few years ago. It's finally about
time to get it out and into an interpreter. I'll add more documentation here as
the project progresses.

A fundamental attribute of Laconic is that there is no real distinction between
functions, loops, conditionals, classes, interfaces, lists, and dictionaries;
all possible desired behaviour from these constructs is available in the single
entity (other than primitives): the "block".

In Laconic, a function is literally a list of statements. Statements may be
executed immediately or may be delayed for later execution (i.e.,
the statement is a first-class construct).

Here are some other major design points:

- There are no keywords. Any words written in the language are user-defined.
- Every operator is a unique character. Every symbol on the standard US
  keyboard is used for an operator, and each one is uniquely defined for that
  operation; no one operator is used for multiple things.
  - Some examples in other languages include C's use of `*` for multiplication
    and dereferencing, and `.` for float literals and member access.
- Laconic supports powerful operator definition and overloading, as the main
  planned use case is for prototyping other languages.
- As much of the language as possible will be defined in the language itself
  (taking inspiration from Lisp)

For fun, here's a program which prints the sum of multiples of 3 below 1000.
`multiples_of_3` is a function which iteratively builds the list of numbers.
`sum` is a function which iterates through the given list, adds them, and
returns the result (as one would expect).

```
!multiples_of_3: $[!i: 0 | %@#: i; i +: 3] i < 1000;

!sum: $[!list: _; !i: 0; %: 0 |
  % +: list@i;
] ++i < #list;

% sum multiples_of_3;
```
