#ifndef BRAINFUCK_INTERPRETER_BEGINLOOP_H
#define BRAINFUCK_INTERPRETER_BEGINLOOP_H
#include "Instruction.h"

class BeginLoop:public Instruction{ // [
    std::size_t exitIndex_;
public:
    BeginLoop(const std::size_t& exitIndex):exitIndex_(exitIndex){}
    void setIndex(const std::size_t& index) override { exitIndex_ = index; }
    void execute (Controller& controller) override {
        if(controller.memory.isZero())
            controller.setInstructionIndex(exitIndex_);
    }
};


#endif //BRAINFUCK_INTERPRETER_BEGINLOOP_H
