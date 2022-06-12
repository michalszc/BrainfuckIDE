#ifndef BRAINFUCK_INTERPRETER_INTERPRETER_H
#define BRAINFUCK_INTERPRETER_INTERPRETER_H
#include <vector>
#include <string>
#include <stack>

#include "RangeError.h"

#include "Brainfuck.h"
#include "Instruction.h"

#include "MoveLeft.h"
#include "MoveRight.h"
#include "Plus.h"
#include "Minus.h"
#include "Output.h"
#include "Input.h"
#include "BeginLoop.h"
#include "EndLoop.h"

class Interpreter{
private:
    std::string inputText_;
    std::string code_;
    instructions_t instructions;
    Controller controller;
public:
    explicit Interpreter(const std::string& code, const std::string& inputText, QTextEdit *output);
    void checkCode(const std::string &code);
    void setInput(const std::string& inputText) { inputText_=inputText; controller.setInputText(inputText); }
    void run();
};

#endif //BRAINFUCK_INTERPRETER_INTERPRETER_H
