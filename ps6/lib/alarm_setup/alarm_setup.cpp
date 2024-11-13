#include "alarm_setup.h"
#include "date_time_setup.h"
#include <EEPROM.h>
#include "../../include/config.h"
#include "../../include/lcd_wrapper.h"
#include "helpers.h"
#include "sounds.h"
#include "IR_remote.h"
extern volatile byte btn_state;

bool configure_alarm(void *alarm_value, enum flag indicator){
    struct dt current_time = now();
    enum IR_Button btn;
    while(true){
        btn = pressed_button();
        print_alarm_value(alarm_value, indicator);
        switch(btn_state){
            case BTN1_PRESSED:
                switch(indicator){
                    case HOURS:
                        current_time.hours = *(byte*)alarm_value;
                        break;
                    case MINUTES:
                        current_time.minutes = *(byte*)alarm_value;
                        break;
                    case SECONDS:
                        current_time.seconds = *(byte*)alarm_value;
                        break;
                    case DAY:
                        current_time.day = *(byte*)alarm_value;
                        break;
                    case MONTH:
                        current_time.month = *(byte*)alarm_value;
                        break;
                    case YEAR:
                        current_time.year = *(int*)alarm_value;
                        break;
                }
                print_alarm_value(alarm_value, indicator);
                btn_state = 0;
                lcd_clear();
                return true;
            case BTN2_PRESSED:
                switch(indicator){
                    case HOURS:
                        *(byte*)alarm_value += 1;        
                        if (*(byte*)alarm_value > 23) {
                            *(byte*)alarm_value = 0;
                        }
                        break;
                    case MINUTES:
                        *(byte*)alarm_value += 1;        
                        if (*(byte*)alarm_value > 59) {
                            *(byte*)alarm_value = 0;
                        }
                        break;
                    case SECONDS:
                        *(byte*)alarm_value += 1;        
                        if (*(byte*)alarm_value > 59) {
                            *(byte*)alarm_value = 0;
                        }
                        break;
                    case DAY:
                        *(byte*)alarm_value += 1;        
                        if (*(byte*)alarm_value > 31) {
                            *(byte*)alarm_value = 1;
                        }
                        break;
                    case MONTH:
                        *(byte*)alarm_value += 1;        
                        if (*(byte*)alarm_value > 12) {
                            *(byte*)alarm_value = 1;
                        }
                        break;
                    case YEAR:
                        *(int*)alarm_value += 1;        
                        if (*(int*)alarm_value > 9999) {
                            *(int*)alarm_value = 0;
                        }
                        break;
                }
                print_alarm_value(alarm_value, indicator);
                btn_state = 0;
                break;
            case BTN3_PRESSED:
                switch(indicator){
                    case HOURS:
                        if (*(byte*)alarm_value == 0) {
                            *(byte*)alarm_value = 23;
                        } else {
                            *(byte*)alarm_value -= 1;
                        }
                        break;
                    case MINUTES:
                        if (*(byte*)alarm_value == 0) {
                            *(byte*)alarm_value = 59;
                        } else {
                            *(byte*)alarm_value -= 1;
                        }
                        break;
                    case SECONDS:
                        if (*(byte*)alarm_value == 0) {
                            *(byte*)alarm_value = 59;
                        } else {
                            *(byte*)alarm_value -= 1;
                        }
                        break;
                    case DAY:
                        *(byte*)alarm_value -= 1;        
                        if (*(byte*)alarm_value < 1) {
                            *(byte*)alarm_value = 31;
                        }
                        break;
                    case MONTH:
                        *(byte*)alarm_value -= 1;        
                        if (*(byte*)alarm_value < 1) {
                            *(byte*)alarm_value = 12;
                        }
                        break;
                    case YEAR:
                        *(int*)alarm_value -= 1;        
                        if (*(int*)alarm_value < 0) {
                            *(int*)alarm_value = 9999;
                        }
                        break;
                }
                print_alarm_value(alarm_value, indicator);
                btn_state = 0;
                break;
            case BTN4_PRESSED:
                lcd_clear();
                lcd_print_at(0, 0, "The alarm was not set");
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

void set_alarm(struct dt alarm_time){
    EEPROM.put(0, alarm_time);
    lcd_clear();
    lcd_print_at(0, 0, "Alarm was set");
    lcd_print_at(1, 0, "successfully!");
    delay(200);
}

bool check_alarm(struct dt alarm_time, struct dt current_time) {
    return (current_time.year == alarm_time.year &&
            current_time.month == alarm_time.month &&
            current_time.day == alarm_time.day && 
            current_time.hours == alarm_time.hours &&
            current_time.minutes == alarm_time.minutes &&
            current_time.seconds == alarm_time.seconds);
}

struct dt read_alarm(){
    struct dt alarm_time;
    EEPROM.get(0, alarm_time);
    return alarm_time;
}

void remove_alarm(){
    struct dt alarm_time;
    alarm_time.year = 0;
    alarm_time.month = 0;
    alarm_time.day = 0;
    alarm_time.hours = 0;
    alarm_time.minutes = 0;
    alarm_time.seconds = 0;
    EEPROM.put(0, alarm_time);
    lcd_clear();
    lcd_print_at(0, 0, "Alarm removed");
    lcd_print_at(1, 0, "successfully!");
    delay(1000);
}

void alarm(struct melody selected_melody) {
    uint32_t start_time = millis();
    uint32_t note_start_time = millis();
    bool display_state = true;
    byte note_index = 0;
    bool playing_note = false;

    lcd_clear();
    lcd_print_at(0, 0, "ALARM TRIGGERED");
    lcd_print_at(1, 0, "BTN2 to stop");

    while (true) {
        if ((btn_state == BTN2_PRESSED && millis() - start_time > 250) || (pressed_button() == IR_BUTTON_2 && millis() - start_time > 250)) {
            lcd_backlight(true);
            lcd_clear();
            lcd_print_at(0, 0, "ALARM STOPPED");
            delay(1000);
            return;
        }
        if((btn_state == BTN3_PRESSED && millis() - start_time > 250) || (pressed_button() == IR_BUTTON_PLUS && millis() - start_time > 250)){
            lcd_backlight(true);
            lcd_clear();
            lcd_print_at(0, 0, "ALARM WAS SNOOZED");
            snooze_alarm(read_alarm());
            return;
        }
        if (millis() - start_time > 1000) {
            display_state = !display_state;
            start_time = millis();
            lcd_clear();
            if (display_state) {
                lcd_print_at(0, 0, "ALARM TRIGGERED");
                lcd_print_at(1, 0, "BTN2 to stop");
                lcd_backlight(true);
            } else {
                lcd_backlight(false);
            }
        }

        if (!playing_note) {
            if (note_index < sizeof(selected_melody.notes) / sizeof(selected_melody.notes[0])) {
                if (selected_melody.notes[note_index] == 0) {
                    delay(selected_melody.pauseBetweenNotes);
                } else {
                    play_note(selected_melody.notes[note_index], selected_melody.noteDuration);
                }
                note_start_time = millis();
                playing_note = true;
                note_index++;
            } else {
                note_index = 0;
            }
        }

        if (playing_note && millis() - note_start_time > selected_melody.noteDuration + selected_melody.pauseBetweenNotes) {
            playing_note = false;
        }
    }
}

void snooze_alarm(struct dt alarm_time){
    alarm_time.minutes += 5;
    if(alarm_time.minutes > 59){
        alarm_time.minutes -= 60;
        alarm_time.hours += 1;
        if(alarm_time.hours > 23){
            alarm_time.hours -= 24;
            alarm_time.day += 1;
        }
    }
    set_alarm(alarm_time);
}