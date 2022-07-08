#ifndef BRAINFUCK_INTERPRETER_MEMORY_H
#define BRAINFUCK_INTERPRETER_MEMORY_H
#include "Brainfuck.h"
#include "RangeError.h"

class Memory{
private:
    std::size_t index{};
    memory_t cells{};
public:
    Memory() = default;
    void increment(){
        if ( index >= MAX_MEMORY_SIZE )
            throw RangeError("Invalid memory index - index out of scope");
        ++index;
    };
    void decrement(){
        if ( index < 1 )
            throw RangeError("Invalid memory index - negative index");
        --index;
    };
    void increment_value(){
        ++cells[index];
    };
    void decrement_value(){
        --cells[index];
    };
    bool isZero() const{
        return cells[index] == 0;
    }
    void set_value(char newValue){
        cells[index] = newValue;
    };
    char get_current_value() const{
        return cells[index];
    };
};


#endif //BRAINFUCK_INTERPRETER_MEMORY_H
