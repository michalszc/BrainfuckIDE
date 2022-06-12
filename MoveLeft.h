#ifndef BRAINFUCK_INTERPRETER_MOVELEFT_H
#define BRAINFUCK_INTERPRETER_MOVELEFT_H
#include "Instruction.h"

class MoveLeft:public Instruction{ // <
public:
    void setIndex(__attribute__((unused)) const std::size_t& index) override {};
    void execute (Controller& controller) override { controller.memory.decrement(); }
};


#endif //BRAINFUCK_INTERPRETER_MOVELEFT_H
