#include "states.h"
#include "sensors.h"
#include "rtc_wrapper.h"
#include "menu_settings.h"
#include "lcd_wrapper.h"
#include "config.h"
#include "helpers.h"
#include "alarm_setup.h"
#include "factory_reset.h"
#include "sounds.h"

enum state state_clock_and_date(){
    struct dt current_time = now();
    print_date_time(current_time);
    delay(500);
    return CLOCK_AND_DATE;
}

enum state state_show_env(){
    print_temperature_humidity();
    delay(500);
    return SHOW_ENV;
}

enum state state_menu(){
    menu_setup();
    return CLOCK_AND_DATE;
}

enum state state_alarm(){
    uint32_t start_time = millis();
    lcd_clear();
    lcd_print_at(0, 0, "Setted alarm:");
    while(millis() - start_time < 1000){
        continue;
    }
    print_alarm();
    return ALARM;
}

enum state state_alarm_triggered(){
    lcd_clear();
    struct melody selected_melody = read_melody();
    alarm(selected_melody);
    remove_alarm();
    return ALARM_TRIGGERED;
}

enum state state_factory_reset(){
    factory_reset();
    return CLOCK_AND_DATE;
}