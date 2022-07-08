#ifndef BRAINFUCK_INTERPRETER_INSTRUCTION_H
#define BRAINFUCK_INTERPRETER_INSTRUCTION_H
#include "Controller.h"
#include "Brainfuck.h"
#include <vector>
#include <memory>

class Instruction{
public:
    virtual void execute(Controller& controller) = 0;
    virtual void setIndex(__attribute__((unused)) const std::size_t& index){};
    virtual ~Instruction() = default;
};

typedef std::vector<std::unique_ptr<Instruction>> instructions_t;

#endif //BRAINFUCK_INTERPRETER_INSTRUCTION_H
