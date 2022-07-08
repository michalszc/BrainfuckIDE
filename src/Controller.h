#ifndef BRAINFUCK_INTERPRETER_CONTROLLER_H
#define BRAINFUCK_INTERPRETER_CONTROLLER_H
#include <QTextEdit>
#include <string>
#include "Memory.h"

class Controller {
private:
    std::size_t instructionIndex_=0;
    std::string input_;
    std::size_t inputIndex=0;
    QTextEdit *output_;
public:
    Memory memory;
public:
    void setOutput(QTextEdit *output) { output_ = output; }
    std::size_t getInstructionIndex() { return instructionIndex_; }
    void IncrementInstructionIndex() { ++instructionIndex_; }
    void setInstructionIndex(std::size_t index){ instructionIndex_ = index; }
    void setInputText(const std::string& input){ input_ = input; }
    void readInput();
    void writeOutput();
};


#endif //BRAINFUCK_INTERPRETER_CONTROLLER_H
