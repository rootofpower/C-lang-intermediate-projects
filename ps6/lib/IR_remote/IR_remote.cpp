#include "IR_remote.h"

NecDecoder ir;

void Inf_Red_Remote(){
    ir.tick();
}

enum IR_Button pressed_button(){
    if(ir.available()){
        switch(ir.readPacket()){
            case 0xFF22DD:
                return IR_BUTTON_PREV;
            case 0xFF02FD:
                return IR_BUTTON_NEXT;
            case 0xFFE01F:
                return IR_BUTTON_MINUS;
            case 0xFFA857:
                return IR_BUTTON_PLUS;
            case 0xFF6897:
                return IR_BUTTON_0;
            case 0xFF30CF:
                return IR_BUTTON_1;
            case 0xFF18E7:
                return IR_BUTTON_2;
            case 0xFF7A85:
                return IR_BUTTON_3;
            case 0xFF10EF:
                return IR_BUTTON_4;
        }
    }
    return BUTTON_NOT_PRESSED;
}
