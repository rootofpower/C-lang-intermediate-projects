#include <Arduino.h>
#include "rtc_wrapper.h"
#include "sensors.h"
#include "lcd_wrapper.h"
#include "states.h"
#include "config.h"
#include "helpers.h"
#include "menu_settings.h"
#include "date_time_setup.h"
#include "alarm_setup.h"
#include <EEPROM.h>
#include "IR_remote.h"

/**
 * Holds combination of pressed buttons.
 */
volatile byte btn_state;


/**
 * ISR for button press.
 *
 * This function is executed, when button is pressed. The global variable
 * `btn_state` is then set according to the combination of pressed buttons.
 */
void on_button_press(){
    btn_state = 0;

    if( digitalRead(BTN1_PIN) == HIGH) {
        btn_state |= BTN1_PRESSED;
    }

    if(digitalRead(BTN2_PIN) == HIGH){
        btn_state |= BTN2_PRESSED;
    }

    if(digitalRead(BTN3_PIN) == HIGH){
        btn_state |= BTN3_PRESSED;
    }

    if(digitalRead(BTN4_PIN) == HIGH){
        btn_state |= BTN4_PRESSED;
    }
}


void setup(){
    // needed from original main() function
    init();

    Serial.begin(9600);
    // while(!Serial.available()){
    //     delay(100);ttachInterrupt(digitalPinToInterrupt(2), on_button_pr
    // }

    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
    pinMode(BTN3_PIN, INPUT);
    pinMode(BTN4_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), on_button_press, RISING);
    attachInterrupt(digitalPinToInterrupt(3), Inf_Red_Remote, FALLING);    
    
    // init alarm clock modules
    lcd_init();
    clock_init();
    sensors_init();
    if (EEPROM.read(INIT_ADDR) != INIT_KEY) { // first time initialization
    EEPROM.write(INIT_ADDR, INIT_KEY);    //write the key to the EEPROM
    }
}


int main() {
    // init
    setup();
    struct dt alarm_time;
    bool alarm_trigger = false;
    enum state state = CLOCK_AND_DATE;
    unsigned long stateChangeTime = millis(); // save the time of the last state change
    // main loop 
    for(;;){
        enum IR_Button btn = pressed_button();
        alarm_time = read_alarm();
        if(check_alarm(alarm_time, now())){
            alarm_trigger = true;
            state = ALARM_TRIGGERED;
        }
        // in loop() 
        switch(btn_state){
            case BTN1_PRESSED:
                state = SHOW_ENV;
                stateChangeTime = millis(); // save the time of the last state change
                btn_state = 0; // reset button state
                break;

            case BTN2_PRESSED:
                state = CLOCK_AND_DATE;
                stateChangeTime = millis(); 
                btn_state = 0; 
                break;

            case BTN3_PRESSED:
                state = ALARM;
                stateChangeTime = millis(); 
                btn_state = 0; 
                break;

            case BTN4_PRESSED:
                state = MENU;
                stateChangeTime = millis(); 
                break;
        }
        switch(btn){
            case IR_BUTTON_1:
                state = SHOW_ENV;
                stateChangeTime = millis(); 
                break;

            case IR_BUTTON_2:
                state = CLOCK_AND_DATE;
                stateChangeTime = millis(); 
                break;

            case IR_BUTTON_3:
                state = ALARM;
                stateChangeTime = millis(); 
                break;

            case IR_BUTTON_4:
                state = MENU;
                stateChangeTime = millis(); 
                break;
            case IR_BUTTON_0:
                state = FACTORY_RESET;
                stateChangeTime = millis(); 
                break;
        }
        if (state != CLOCK_AND_DATE && millis() - stateChangeTime > 5000 && !alarm_trigger) {
            state = CLOCK_AND_DATE;
        }
        switch(state){
            case CLOCK_AND_DATE:
                lcd_clear();
                state = state_clock_and_date();
                break;

            case SHOW_ENV:
                lcd_clear();
                state = state_show_env();
                break;

            case MENU:
                lcd_clear();
                state = state_menu();
                break;

            case ALARM:
                lcd_clear();   
                state = state_alarm();
                break;
            case ALARM_TRIGGERED:
                lcd_clear();
                state = state_alarm_triggered();
                alarm_trigger = false;
                lcd_backlight(true);
                break;
            case FACTORY_RESET:
                lcd_clear();
                state = state_factory_reset();
                break;
        }
    }
}
