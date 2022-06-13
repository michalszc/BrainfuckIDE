#ifndef BRAINFUCK_INTERPRETER_OUTPUT_H
#define BRAINFUCK_INTERPRETER_OUTPUT_H
#include "Instruction.h"

class Output:public Instruction{ // .
public:
    void execute (Controller& controller) override { controller.writeOutput(); }
};

#endif //BRAINFUCK_INTERPRETER_OUTPUT_H
