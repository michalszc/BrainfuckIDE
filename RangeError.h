#ifndef BRAINFUCK_INTERPRETER_RANGEERROR_H
#define BRAINFUCK_INTERPRETER_RANGEERROR_H
#include <exception>
#include <string>

class RangeError: public std::exception{
private:
    std::string message_;
public:
    explicit RangeError(const std::string& message): message_(message){}
    const char* what() const noexcept override { return message_.c_str(); }
};


#endif //BRAINFUCK_INTERPRETER_RANGEERROR_H
