#include <NecDecoder.h>
#include "../../include/config.h"

void Inf_Red_Remote();

enum IR_Button {
    IR_BUTTON_1,
    IR_BUTTON_2,
    IR_BUTTON_3,
    IR_BUTTON_4,
    IR_BUTTON_0,
    IR_BUTTON_MINUS,
    IR_BUTTON_PLUS,
    IR_BUTTON_PREV,
    IR_BUTTON_NEXT,
    BUTTON_NOT_PRESSED
};

enum IR_Button pressed_button();

