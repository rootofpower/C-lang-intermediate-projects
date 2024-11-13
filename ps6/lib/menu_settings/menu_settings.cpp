#include "menu_settings.h"
#include <Arduino.h>
#include "../../include/lcd_wrapper.h"
#include "../../include/config.h"
#include "../../include/rtc_wrapper.h"
#include "date_time_setup.h"
#include "alarm_setup.h"
#include "helpers.h"
#include "IR_remote.h"
#include "sounds.h"
#include "factory_reset.h"
extern volatile byte btn_state;

void menu_setup(){
    lcd_clear();
    char* menu[] = {"Menu", "Set time", "Set date", "Set alarm", "Dismiss alarm", "Factory reset", "Select melody"};
    print_menu(menu[0], menu[1]);
    print_cursor(1, 0);
    byte menu_index = 1;
    btn_state = 0;
    enum IR_Button btn;
    uint32_t start_time = millis();
    while (millis() - start_time < 30000){
        btn = pressed_button();
        switch(btn_state){
            case BTN1_PRESSED:
                btn_state = 0;
                menu_index = menu_setting(menu_index);
                print_menu(menu[menu_index - 1], menu[menu_index]);
                break;
            case BTN2_PRESSED:
                btn_state = 0;
                menu_index++;
                if (menu_index > sizeof(menu) / sizeof(menu[0]) - 1){
                    menu_index = 1;
                }
                print_menu(menu[menu_index - 1], menu[menu_index]);
                print_cursor(1, 0);
                break;
            case BTN3_PRESSED:
                btn_state = 0;
                menu_index--;
                if (menu_index < 1) {
                    menu_index = sizeof(menu) / sizeof(menu[0]) - 1;
                }
                print_menu(menu[menu_index - 1], menu[menu_index]);
                print_cursor(1, 0);
                break;
            case BTN4_PRESSED:
                btn_state = 0;
                lcd_clear();
                return;
        }
        switch(btn){
            case IR_BUTTON_NEXT:
                btn_state = 0;
                menu_index = menu_setting(menu_index);
                print_menu(menu[menu_index - 1], menu[menu_index]);
                break;
            case IR_BUTTON_PLUS:
                btn_state = 0;
                menu_index++;
                if (menu_index > sizeof(menu) / sizeof(menu[0]) - 1){
                    menu_index = 1;
                }
                print_menu(menu[menu_index - 1], menu[menu_index]);
                print_cursor(1, 0);
                break;
            case IR_BUTTON_MINUS:
                btn_state = 0;
                menu_index--;
                if (menu_index < 1) {
                    menu_index = sizeof(menu) / sizeof(menu[0]) - 1;
                }
                print_menu(menu[menu_index - 1], menu[menu_index]);
                print_cursor(1, 0);
                break;
            case IR_BUTTON_PREV:
                btn_state = 0;
                lcd_clear();
                return;
        }
    }
}

byte menu_setting(byte menu_index){
    switch(menu_index){
        case 1:
            lcd_clear();
            setup_time();
            break;
        case 2:
            lcd_clear();
            setup_date();
            break;
        case 3:
            lcd_clear();
            setup_alarm();
            break;
        case 4:
            lcd_clear();
            remove_alarm();
            break;
        case 5:
            lcd_clear();
            factory_reset();
            break;
        case 6:
            lcd_clear();
            struct melody selected = select_melody(melodies());
            write_melody(selected);
            break;
    }
    return menu_index;
    btn_state = 0;
}

void setup_time(){
    struct dt time = now();
    if(!configure_time_and_date(&time.hours, HOURS)){
        return;
    }
    else if(!configure_time_and_date(&time.minutes, MINUTES)){
        return;
    }
    else if(!configure_time_and_date(&time.seconds, SECONDS)){
        return;
    }
    else{
        set_time(time.hours, time.minutes, time.seconds);
        delay(200);
        return;
    }
}

void setup_date(){
    struct dt date = now();
    if(!configure_time_and_date(&date.year, YEAR)){
        return;
    }
    else if(!configure_time_and_date(&date.month, MONTH)){
        return;
    }
    else if(!configure_time_and_date(&date.day, DAY)){
        return;
    }
    else {
        set_date(date.day, date.month, date.year);
        delay(200);
    }
}

void setup_alarm(){
    struct dt alarm_time = now();
    if(!configure_alarm(&alarm_time.year, YEAR)){
        return;
    }
    else if(!configure_alarm(&alarm_time.month, MONTH)){
        return;
    }
    else if(!configure_alarm(&alarm_time.day, DAY)){
        return;
    }
    else if(!configure_alarm(&alarm_time.hours, HOURS)){
        return;
    }
    else if(!configure_alarm(&alarm_time.minutes, MINUTES)){
        return;
    }
    else if(!configure_alarm(&alarm_time.seconds, SECONDS)){
        return;
    }
    else{
        set_alarm(alarm_time);
        delay(200);
    }
}

