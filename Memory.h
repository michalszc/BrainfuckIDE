#ifndef BRAINFUCK_INTERPRETER_MEMORY_H
#define BRAINFUCK_INTERPRETER_MEMORY_H
#include "Brainfuck.h"


class Memory{
private:
    std::size_t index{};
    memory_t cells{};
public:
    Memory() = default;
    void increment(){
        if ( index < MAX_MEMORY_SIZE ) // REPLACE WITH EXCEPTION
            ++index;
    };
    void decrement(){
        if ( index >= 1 ) // REPLACE WITH EXCEPTION
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
