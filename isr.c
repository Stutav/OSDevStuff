#include "defines.h"

void exception_handler(uint8_t id){
    switch(id){
        case 0:
            terminal_writestring("Exception 0!");
            break;
        case 3:
            terminal_writestring("Exception 3!");
            break;
        case 8:
            terminal_writestring("Exception 8!");
            break;
        default:
            terminal_writestring("Weird Exception!");
            break;
    }
}