#ifndef BRAINFUCK_INTERPRETER_MINUS_H
#define BRAINFUCK_INTERPRETER_MINUS_H
#include "Instruction.h"

class Minus:public Instruction{ // -
public:
    void execute (Controller& controller) override { controller.memory.decrement_value(); }
};


#endif //BRAINFUCK_INTERPRETER_MINUS_H
