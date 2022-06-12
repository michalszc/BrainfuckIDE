#ifndef BRAINFUCK_INTERPRETER_INSTRUCTION_H
#define BRAINFUCK_INTERPRETER_INSTRUCTION_H
#include "Controller.h"
#include "Brainfuck.h"
#include <vector>
#include <memory>

class Instruction{
public:
    virtual void execute(Controller& controller) = 0;
    virtual void setIndex(const std::size_t& index) = 0;
    virtual ~Instruction() = default;
};

typedef std::vector<std::unique_ptr<Instruction>> instructions_t;

#endif //BRAINFUCK_INTERPRETER_INSTRUCTION_H
