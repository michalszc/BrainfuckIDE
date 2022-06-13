#include "Interpreter.h"
#include <QDebug>

Interpreter::Interpreter(const std::string &code, const std::string& inputText, QTextEdit *output) {
    try{
        controller.setOutput(output);
        setInput(inputText);
        checkCode(code);
        run();
    }catch(std::exception& e){
        QColor prev = output->textColor();
        output->setTextColor(Qt::red);
        output->setText(QString("Error: ")+QString(e.what()));
        output->setTextColor(prev);
    }
}

void Interpreter::checkCode(const std::string &code) {
    std::stack<size_t> openBrackets;
    for(const char& c: code){
        switch (c) {
            case '<':
                code_ += '<';
                instructions.emplace_back(new MoveLeft());
                break;
            case '>':
                code_ += '>';
                instructions.emplace_back(new MoveRight());
                break;
            case '+':
                code_ += '+';
                instructions.emplace_back(new Plus());
                break;
            case '-':
                code_ += '-';
                instructions.emplace_back(new Minus());
                break;
            case '.':
                code_ += '.';
                instructions.emplace_back(new Output());
                break;
            case ',':
                code_ += ',';
                instructions.emplace_back(new Input());
                break;
            case '[':
                code_ += '[';
                openBrackets.push(instructions.size());
                instructions.emplace_back(new BeginLoop(-1));
                break;
            case ']':
                code_ += ']';
                if(!openBrackets.empty()){
                    const size_t i = openBrackets.top();
                    openBrackets.pop();
                    instructions[i]->setIndex(instructions.size());
                    instructions.emplace_back(new EndLoop(i));
                }else{
                    throw RangeError("Mismatched brackets (extra right bracket)");
                }
                break;
            default:
                continue;
        }
    }
    if (!openBrackets.empty())
        throw RangeError("Mismatched brackets (extra left bracket)");
}

void Interpreter::run() {
    size_t i = controller.getInstructionIndex();
    while(i < instructions.size()){
        instructions[i]->execute(controller);
        controller.IncrementInstructionIndex();
        i = controller.getInstructionIndex();
    }
}
