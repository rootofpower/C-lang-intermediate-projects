#include "sounds.h"
#include "../../include/config.h"
#include "../../include/lcd_wrapper.h"
#include "IR_remote.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "../../include/rtc_wrapper.h"

extern volatile byte btn_state;

void play_note(int noteFrequency, int noteDuration) {
    tone(BUZZER_PIN, noteFrequency, noteDuration);
    delay(noteDuration + 20); 
    noTone(BUZZER_PIN);
}

void play_alarm(struct melody melody) {
    for (int i = 0; i < sizeof(melody.notes) / sizeof(melody.notes[0]); i++) {
        if (melody.notes[i] == 0) {
            delay(melody.pauseBetweenNotes);
        } else {
            play_note(melody.notes[i], melody.noteDuration);
            delay(melody.pauseBetweenNotes);
        }
    }
}

struct melody select_melody(struct melody melody[]) {
    enum IR_Button btn;
    int melody_index = 0;
    for(;;){
        btn = pressed_button();
        lcd_print_at(0, 0, "Select melody:");
        lcd_print_at(1, 0, melody[melody_index].name);
        switch(btn_state){
            case BTN1_PRESSED:
                btn_state = 0;
                lcd_clear();
                return melody[melody_index];
            case BTN2_PRESSED:
                melody_index++;
                if (melody_index > sizeof(melody) / sizeof(melody[0]) - 1) {
                    melody_index = 0;
                }
                btn_state = 0;
                lcd_clear();
                break;
            case BTN3_PRESSED:
                melody_index--;
                if (melody_index < 0) {
                    melody_index = sizeof(melody) / sizeof(melody[0]) - 1;
                }
                btn_state = 0;
                lcd_clear();
                break;
            case BTN4_PRESSED:
                btn_state = 0;
                lcd_clear();
                return melody[0];
        }
        switch(btn) {
            case IR_BUTTON_NEXT:
                lcd_clear();
                return melody[melody_index];
            case IR_BUTTON_PLUS:
                melody_index--;
                if (melody_index < 0) {
                    melody_index = sizeof(melody) / sizeof(melody[0]) - 1;
                }
                lcd_clear();
                break;
            case IR_BUTTON_MINUS:
                melody_index++;
                if (melody_index > sizeof(melody) / sizeof(melody[0]) - 1){
                    melody_index = 0;
                }
                lcd_clear();
                break;
            case IR_BUTTON_PREV:
                lcd_clear();
                return melody[0];
        }
    }

}

struct melody* melodies(){
    static struct melody melodies[] = {
        {
            "He's a Pirate",
            300,   
            50, 
            { 659, 659, 659, 523, 784, 523, 659, 523,
              659, 659, 659, 523, 784, 523, 659, 523,
              784, 784, 784, 784, 698, 698, 698, 659, 698, 784, 659, 523, 0 } 
        },
        {
           "Smth in the Way",
            300,   
            300,   
            { 220, 247, 220, 165, 220, 0, 220, 0,
            220, 247, 220, 165, 220, 0, 220, 0,
            220, 247, 220, 165, 220, 0, 220, 0,
            220, 247, 220, 165, 220, 0, 220, 0 } 
        }
    };
    return melodies;
}

void write_melody(struct melody melody) {
    EEPROM.put(sizeof(struct dt), melody);
    delay(250);
}

struct melody read_melody() {
    struct melody melody;
    EEPROM.get(sizeof(struct dt), melody);
    return melody;
}
