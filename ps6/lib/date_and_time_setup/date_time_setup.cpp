#include "date_time_setup.h"
#include "../../include/rtc_wrapper.h"
#include "../../include/config.h"
#include "../../include/lcd_wrapper.h"
#include "helpers.h"
#include "IR_remote.h"

extern volatile byte btn_state;

bool configure_time_and_date(void *value, enum flag indicator){
    enum IR_Button btn;
    struct dt current_time = now();
    for(;;){
        btn = pressed_button();
        print_value(value, indicator);
        switch(btn_state){
            case BTN1_PRESSED:
                switch(indicator){
                    case HOURS:
                        current_time.hours = *(byte*)value;
                        break;
                    case MINUTES:
                        current_time.minutes = *(byte*)value;
                        break;
                    case SECONDS:
                        current_time.seconds = *(byte*)value;
                        break;
                    case DAY:
                        current_time.day = *(byte*)value;
                        break;
                    case MONTH:
                        current_time.month = *(byte*)value;
                        break;
                    case YEAR:
                        current_time.year = *(int*)value;
                        break;
                }
                print_value(value, indicator);
                btn_state = 0;
                lcd_clear();
                return true;
            case BTN2_PRESSED:
                switch(indicator){
                    case HOURS:
                        *(byte*)value += 1;        
                        if (*(byte*)value > 23) {
                            *(byte*)value = 0;
                        }
                        break;
                    case MINUTES:
                        *(byte*)value += 1;        
                        if (*(byte*)value > 59) {
                            *(byte*)value = 0;
                        }
                        break;
                    case SECONDS:
                        *(byte*)value += 1;        
                        if (*(byte*)value > 59) {
                            *(byte*)value = 0;
                        }
                        break;
                    case YEAR:
                        *(int*)value += 1;        
                        if (*(int*)value > 9999) {
                            *(int*)value = 1;
                        }
                        break;
                    case MONTH:
                        *(byte*)value += 1;        
                        if (*(byte*)value > 12) {
                            *(byte*)value = 1;
                        }
                        break;
                    case DAY:
                        *(byte*)value += 1;
                        byte max_days = days_in_month(current_time.month, current_time.year);
                        if (*(byte*)value > max_days) {
                            *(byte*)value = 1;
                        }
                        break;
                }
                print_value(value, indicator);
                btn_state = 0;
                break;
            case BTN3_PRESSED:
                switch (indicator) {
                    case HOURS:
                        if (*(byte*)value == 0) {
                            *(byte*)value = 23;
                        } else {
                            *(byte*)value -= 1;
                        }
                        break;
                    case MINUTES:
                        if (*(byte*)value == 0) {
                            *(byte*)value = 59;
                        } else {
                            *(byte*)value -= 1;
                        }
                        break;
                    case SECONDS:
                        if (*(byte*)value == 0) {
                            *(byte*)value = 59;
                        } else {
                            *(byte*)value -= 1;
                        }
                        break;
                    case YEAR:
                        *(int*)value -= 1;        
                        if (*(int*)value < 1) {
                            *(int*)value = 9999;
                        }
                        break;
                    case MONTH:
                        *(byte*)value -= 1;        
                        if (*(byte*)value < 1) {
                            *(byte*)value = 12;
                        }
                        break;
                    case DAY:
                        *(byte*)value -= 1;
                        if (*(byte*)value < 1) {
                            *(byte*)value = days_in_month(current_time.month, current_time.year);
                        }
                        break;
                }
                print_value(value, indicator);
                btn_state = 0;
                break;
            case BTN4_PRESSED:
                lcd_clear();
                switch(indicator){
                    case HOURS:
                        *(byte*)value = current_time.hours;
                        break;
                    case MINUTES:
                        *(byte*)value = current_time.minutes;
                        break;
                    case SECONDS:
                        *(byte*)value = current_time.seconds;
                        break;
                    case DAY:
                        *(byte*)value = current_time.day;
                        break;
                    case MONTH:
                        *(byte*)value = current_time.month;
                        break;
                    case YEAR:
                        *(int*)value = current_time.year;
                        break;
                }
                btn_state = 0;
                return false; 
        }
        switch(btn){
            case IR_BUTTON_NEXT:
                btn_state = BTN1_PRESSED;
                break;
            case IR_BUTTON_PLUS:
                btn_state = BTN2_PRESSED;
                break;
            case IR_BUTTON_MINUS:
                btn_state = BTN3_PRESSED;
                break;
            case IR_BUTTON_PREV:
                btn_state = BTN4_PRESSED;
                break;
        }
    }
}

void print_value(void *value, enum flag indicator){
    lcd_clear();
    switch (indicator){
        case HOURS:
            lcd_print_at(0, 0, "Set hours");
            lcd_print_at(1, 0, "Hours: ");
            print_number(*(byte*)value);
            break;
        case MINUTES:
            lcd_print_at(0, 0, "Set minutes");
            lcd_print_at(1, 0, "Minutes: ");
            print_number(*(byte*)value);
            break;
        case SECONDS:
            lcd_print_at(0, 0, "Set seconds");
            lcd_print_at(1, 0, "Seconds: ");
            print_number(*(byte*)value);
            break;
        case DAY:
            lcd_print_at(0, 0, "Set day");
            lcd_print_at(1, 0, "Day: ");
            print_number(*(byte*)value);
            break;
        case MONTH:
            lcd_print_at(0, 0, "Set month");
            lcd_print_at(1, 0, "Month: ");
            print_number(*(byte*)value);
            break;
        case YEAR:
            lcd_print_at(0, 0, "Set year");
            lcd_print_at(1, 0, "Year: ");
            print_number(*(int*)value);
            break;
    }
    delay(200);
}

byte days_in_month(byte month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                return 29; // Leap year
            else
                return 28;
        default:
            return 31;
    }
}

