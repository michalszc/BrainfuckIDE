# Brainfuck IDE
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)![Brainfuck](https://img.shields.io/badge/-Brainfuck-white?style=for-the-badge)

_An intuitive, featureful and visually appealing Brainfuck IDE built in C++ using Qt library._

**Brainfuck IDE** is a code editor that allows you to write and execute **Brainfuck** code. It's perfect for anybody who just wants to quickly write and run some code  on their computer.

## What's Brainfuck?

**Brainfuck** is the most famous esoteric programming language. It was invented by Urban Müller in 1993. Notable for its extreme minimalism, the language consists of only eight simple commands, a data pointer and an instruction pointer. It is a fully Turing-complete language. The language's name is a reference to the slang term brainfuck, which refers to things so complicated or unusual that they exceed the limits of one's understanding.

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

## Features
- Syntax highlighting
- Code examples
- Themes dark, light and custom one
- Command line options:
  -  `-f <filename>` or `--file <filename>` - File to open(only with .bf extension)
  -  `-t <theme>` or `--theme <theme>` - Change theme, possible options: light, dark and custom(default is dark)
  -  `-c <code>` or `--code <code>` - Set code(Only if file is not set)
  -  `-r` or `--run` - Run code

## Used in the project
- Example codes from [Brainfuck.org](http://brainfuck.org/)
- [QtAwesome](https://github.com/gamecreature/QtAwesome) library to add [Font Awesome](https://fontawesome.com/) icons

## License
[![Licence](https://img.shields.io/github/license/michalszc/BrainfuckIDE?style=for-the-badge)](./LICENSE)
