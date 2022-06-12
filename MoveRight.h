#ifndef BRAINFUCK_INTERPRETER_MOVERIGHT_H
#define BRAINFUCK_INTERPRETER_MOVERIGHT_H
#include "Instruction.h"

class MoveRight:public Instruction{ // >
public:
    void setIndex(__attribute__((unused)) const std::size_t& index) override {};
    void execute (Controller& controller) override { controller.memory.increment(); }
};



#endif //BRAINFUCK_INTERPRETER_MOVERIGHT_H
