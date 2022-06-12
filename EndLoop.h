#ifndef BRAINFUCK_INTERPRETER_ENDLOOP_H
#define BRAINFUCK_INTERPRETER_ENDLOOP_H
#include "Instruction.h"

class EndLoop:public Instruction{ // ]
    std::size_t enterIndex_;
public:
    EndLoop(const std::size_t& enterIndex):enterIndex_(enterIndex){}
    void setIndex(__attribute__((unused)) const std::size_t& index) override {};
    void execute (Controller& controller) override {
        if(!controller.memory.isZero())
            controller.setInstructionIndex(enterIndex_);
    }
};


#endif //BRAINFUCK_INTERPRETER_ENDLOOP_H
