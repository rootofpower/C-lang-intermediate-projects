#ifndef _SOUNDS_H
#define _SOUNDS_H
#define STANDART_MELODY 0
#include <Arduino.h>

struct melody{
    char* name;
    int pauseBetweenNotes;
    int noteDuration;
    int notes[50];
};
/**
 * Play a note with a given frequency and duration
 * 
 * @param noteFrequency The frequency of the note to play
 * @param noteDuration The duration of the note to play
*/

void play_note(int noteFrequency, int noteDuration);


/**
 * Play the alarm sound
*/
void play_alarm(struct melody melody);

/**
 * Select a melody
 * 
 * @param melody The melodies to select from
 * @return The selected melody
*/

struct melody select_melody(struct melody* melody);

/**
 * Get the melodies
 * 
 * @return The melodies
*/
struct melody* melodies();

/**
 * Write a melody to EEPROM storage
 * 
 * @param melody The melody to write
*/
void write_melody(struct melody melody);

/**
 * Get a melody from EEPROM storage
 * 
 * @return The melody
*/
struct melody read_melody();


#endif