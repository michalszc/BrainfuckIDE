#ifndef BRAINFUCK_INTERPRETER_INPUT_H
#define BRAINFUCK_INTERPRETER_INPUT_H
#include "Instruction.h"

class Input:public Instruction { // ,
public:
    void execute (Controller& controller) override { controller.readInput(); }
};


#endif //BRAINFUCK_INTERPRETER_INPUT_H
