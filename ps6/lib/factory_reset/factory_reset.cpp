#include "factory_reset.h"
#include "../../include/config.h"
#include "../../include/lcd_wrapper.h"
#include "../../include/rtc_wrapper.h"
#include "helpers.h"
#include "IR_remote.h"
#include "sounds.h"

extern volatile byte btn_state;

void factory_reset(){
    lcd_print_at(0, 0, "You really want to");
    lcd_print_at(1, 0, "reset the device?");
    enum IR_Button btn;
    uint32_t start_time = millis();
    bool text_changed = false;

    while (true) {
        btn = pressed_button();
        if (millis() - start_time >= 1000 && !text_changed) {
            lcd_clear();
            lcd_print_at(0, 0, "YES press BTN1");
            lcd_print_at(1, 0, " NO press BTN4");
            text_changed = true;
        }

        switch(btn_state){
            case BTN4_PRESSED:
                btn_state = 0;
                lcd_clear();
                return;
            case BTN1_PRESSED:
                btn_state = 0;
                lcd_clear();
                set_datetime(1, 1, 2020, 0, 0, 0);
                struct melody* melody = melodies();
                write_melody(melody[STANDART_MELODY]);
                lcd_print_at(0, 0, "Device reseted");
                lcd_print_at(1, 0, "successfully");
                delay(1000);  
                lcd_clear();
                return;
            
        }
        switch(btn){
            case IR_BUTTON_NEXT:
                btn_state = BTN1_PRESSED;
                break;
            case IR_BUTTON_PREV:
                btn_state = BTN4_PRESSED;
                break;
               
        }
    }

}
