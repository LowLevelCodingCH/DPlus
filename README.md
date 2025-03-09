# D+
## Contents:
### Dependencies
### Procedures
### Variables
### Keywords
### Words
### Strings
### Lexing
### Syntactical Analysis (SYNA)
### Parsing......................................Not Implemented Yet
### Code Generation (ASM)

## Dependencies:
NASM, CBUILD (My C Build System) and a linker

## Procedures:
Procedures are defined with the `proc` keyword and may not return any value.
Procedures are the only thing that exists in this language. And every variable is global.
There are no functions.

## Variables:
Variables are put like so:
`NAME equ VALUE` in NASM.
So like #defines.
I'll say it is functional and call it a day.

## Keywords:
Keywords are the single words in a program like: `proc` or `return`.
`return` does exist as a keyword, but it doesn't take any arguments like 0.
Procedures should return with `return`, while the `main` procedure should return with `exit(<code>)`.

## Words:
Words are symbols like `int` or `main`.

## Strings:
Strings have a length `SL` and a value `SV` with a number `0..2147483647` or `0` .. 2³²-1.
That because the counter is not unsigned but starts with 0.

## Lexing:
Lexing is where the code gets split up into tokens, a.k.a. where this:


```c++
proc main() {
    write("Hello world!");
}
```

becomes this:

```c++
[KEYWORD]: proc
[WORD]: main
[OPEN_PARENTHESIS]: 
[CLOSED_PARENTHESIS]: 
[OPEN_BRACE]: 
[WORD]: write
[OPEN_PARENTHESIS]: 
[STRING_LITERAL]: "Hello, World!"
[CLOSED_PARENTHESIS]: 
[SEMI_COLON]: 
[CLOSED_BRACE]: 
```

## Code Generation (ASM):
```asm
; D+ ASSEMBLY GENERATED
section .text
  global _start

_start:
  ; WRITE
  mov rax, 1
  mov rdi, 1
  mov rsi, SV0
  mov rdx, SL0
  syscall


section .data
SV0: db "Hello, world!", 0xa
SL0 equ $ - SV0
```
