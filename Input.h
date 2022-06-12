#ifndef BRAINFUCK_INTERPRETER_INPUT_H
#define BRAINFUCK_INTERPRETER_INPUT_H
#include "Instruction.h"

class Input:public Instruction { // ,
public:
    void setIndex(__attribute__((unused)) const std::size_t& index) override {};
    void execute (Controller& controller) override { controller.readInput(); }
};


#endif //BRAINFUCK_INTERPRETER_INPUT_H
