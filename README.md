# Brainfuck IDE

_An intuitive, featureful and visually appealing Brainfuck IDE built in C++ using Qt library._

## Brainfuck

Brainfuck is the most famous esoteric programming language. It was invented by Urban Müller in 1993. Notable for its extreme minimalism, the language consists of only eight simple commands, a data pointer and an instruction pointer. It is a fully Turing-complete language. The language's name is a reference to the slang term brainfuck, which refers to things so complicated or unusual that they exceed the limits of one's understanding.

## Commands 

| Character | Meaning |
|-----------|-----------------------------|
| `>`         | Move the cell pointer right. |
| `<`        | Move the cell pointer left.  |
| `+`         | Increment the current cell's value. |
| `-`         | Decrement the current cell's value. |
| `.`         | Print a byte. |
| `,`         | Read a byte.  |
| `[`         | Start a loop. |
| `]`         | End a loop. |

## Rules

- Any arbitrary character besides the 8 listed above is ignored and considered as comments.
- Memory is one-dimensional array of 30,000 byte cells initialized to zero at the beginning of the program.
- The memory pointer starts out on the very left most memory block.
- Loops may be nested as many times as you want.
