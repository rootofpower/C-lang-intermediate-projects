#include "lcd_wrapper.h"
#include "config.h"
#include "states.h"
#include "sensors.h"
#include "rtc_wrapper.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_init(){
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.clear();
    byte Alarm_Clock[] = {
    B11011,
    B11011,
    B01110,
    B10101,
    B10111,
    B10001,
    B01110,
    B10001
    };
    lcd.createChar(0, Alarm_Clock); 
}

void lcd_clear(){
    lcd.clear();
}

void lcd_set_cursor(int y, int x){
    lcd.setCursor(x, y);
}

void lcd_print(char* text){
    lcd.print(text);
}

void lcd_print_at(int y, int x, char* text){
    lcd_set_cursor(y, x);
    lcd_print(text);
}

void lcd_backlight(bool state){
    if(state){
        lcd.backlight();
    } else {
        lcd.noBacklight();
    }
}

void print_custom_symbol(int x, int y, int symbol){
    lcd_set_cursor(y, x);
    lcd.write(symbol);
}
