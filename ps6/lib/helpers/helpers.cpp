#include "helpers.h"
#include "../../include/lcd_wrapper.h"
#include "../../include/sensors.h"
#include "date_time_setup.h"
#include <EEPROM.h>

// code is stolen from:
// https://www.e-tinkers.com/2020/01/do-you-know-arduino-sprintf-and-floating-point/
template <typename... T> void print(const char *str, T... args) {
  int len = snprintf(NULL, 0, str, args...);
  if (len) {
    char buff[len + 1];
    snprintf(buff, len + 1, str, args...);
    Serial.print(buff);
  }
}


void print_date_time(const dt &datetime) {
    char buffer[20];

    snprintf(buffer, sizeof(buffer), "Date: %02d/%02d/%04d", datetime.day, datetime.month, datetime.year);
    lcd_print_at(1, 0, buffer);

    snprintf(buffer, sizeof(buffer), "Time: %02d:%02d:%02d", datetime.hours, datetime.minutes, datetime.seconds);
    lcd_print_at(0, 1, buffer);
}

void print_temperature_humidity() {
    char buffer[20];

    snprintf(buffer, sizeof(buffer), "Temp: %.1f C", get_temperature());
    lcd_print_at(0, 1, buffer);

    snprintf(buffer, sizeof(buffer), "Hum: %d %%", get_humidity());
    lcd_print_at(1, 3, buffer);
}

void print_number(int number) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", number);
    lcd_print_at(1, 11, buffer);
}

void print_alarm_value(void *alarm_value, enum flag indicator) {
    char buffer[20];
    lcd_print_at(0, 0, "Setting alarm");
    switch(indicator){
        case YEAR:
            snprintf(buffer, sizeof(buffer), "Year: %d", *(int*)alarm_value);
            break;
        case MONTH:
            snprintf(buffer, sizeof(buffer), "Month: %d", *(byte*)alarm_value);
            break;
        case DAY:
            snprintf(buffer, sizeof(buffer), "Day: %d", *(byte*)alarm_value);
            break;
        case HOURS:
            snprintf(buffer, sizeof(buffer), "Hours: %d", *(byte*)alarm_value);
            break;
        case MINUTES:
            snprintf(buffer, sizeof(buffer), "Minutes: %d", *(byte*)alarm_value);
            break;
        case SECONDS:
            snprintf(buffer, sizeof(buffer), "Seconds: %d", *(byte*)alarm_value);
            break;
    }
    lcd_print_at(1, 0, buffer);
}


void print_cursor(int x, int y){
    lcd_set_cursor(x, y);
    lcd_print(">");
}

void print_menu(char* first_element, char* second_element){
    lcd_clear();
    lcd_print_at(0, 8-(strlen(first_element) / 2), first_element);
    lcd_print_at(1, 8-(strlen(second_element) / 2), second_element);
}

void print_alarm(){
    struct dt alarm_time;
    EEPROM.get(0, alarm_time);
    uint32_t start_time = millis();

    if(alarm_time.year == 0){
        lcd_print_at(1, 1, "No alarm set");
    }
    else{
        lcd_clear();
        print_custom_symbol(0, 0, 0);
        print_date_time(alarm_time);
        print_custom_symbol(15, 0, 0);
    }
    while(millis() - start_time < 3000){
        continue;
    }
    lcd_clear();
    lcd_print_at(0, 0, "Getting back...");
    start_time = millis();
    while (millis() - start_time < 1000) {
        continue;
    }
    lcd_clear();
}
