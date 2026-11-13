# CSCI 4536: Structures of Programming Languages

Coursework from **CSCI 4536: Structures of Programming Languages** at the **University of New Haven**, Fall 2025 (fourth year, fall semester).

- **Author:** Ryan Godburn
- **Partner:** Matthew Williams (circle labs and the Forth lexer)
- **Languages:** Scheme, Forth, C++

Several labs implement the same circle-statistics program in different languages.

## Files

| File | Language | What it does |
| --- | --- | --- |
| `circles.f` | Forth | Lab 2: integer-only circle tables. Takes diameters from the stack and prints the radius, circumference and area for each, using π ≈ 22/7 with Forth's `*/` scaled multiply-divide. A `0` on the stack works as a stop sentinel. |
| `circle.scm` | Scheme | Lab 7: reads diameters until you enter `0`, rejects negative values, and prints the radius, circumference and area in floating point. |
| `circle-rational.scm` | Scheme | Lab 7 extra credit: the same program in exact rational arithmetic with π ≈ 355/113, showing exact fractions alongside decimal approximations. |
| `gcd.sch` | Scheme | Reads pairs of integers and prints their greatest common divisor using Euclid's algorithm, until you enter `0 0`. |
| `main.cpp` | C++ | Assignment 3: a lexical analyzer for Forth, a state machine that splits Forth source into words, numbers and string literals, recognizes `\` and `( ... )` comments, and writes the comments and a symbol table to a file. |
| `dumps.txt`, `dumpA.txt`, `dumpB.txt`, `dumpC.txt` | Forth | Memory dumps from a Forth session, used to study how the dictionary stores variables, constants and compiled word definitions. |

## Running

```bash
# Forth (for example Gforth): load the file, push diameters, then run
gforth circles.f
11 12 run

# Scheme: each .scm file starts itself when loaded (gcd.sch: call (run))
racket -f circle.scm            # or another Scheme, e.g. guile circle.scm

# Forth lexer
g++ -std=c++17 -o forthlexer main.cpp
./forthlexer circles.f          # writes the token table to output.txt
```

---

*Archived coursework, shared as part of my portfolio. If you're taking this course now, please follow your instructor's academic integrity policy.*
