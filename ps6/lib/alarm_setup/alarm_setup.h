#ifndef _ALARM_SETUP_H
#define _ALARM_SETUP_H

#include <Arduino.h>
#include "date_time_setup.h"
#include "sounds.h"

/**
 * Setup alarm value
 *
 * Sets up alarm value with the given indicator, 
 * which is used to determine which part of the alarm value
 * we want to change.
 * @param alarm_value the alarm value
 * @param indicator the indicator
 * @return true if setup is successful, false otherwise
 */

bool configure_alarm(void *alarm_value, enum flag indicator);

/**
 * Write alarm value to EEPROM storage
 * 
 * Writes alarm value structure to EEPROM storage.
 * @param alarm_value the alarm value structure
*/
void set_alarm(struct dt alarm_time);

/**
 * Check alarm
 * 
 * Checks if the alarm time is equal to the current time.
 * @param alarm_time the alarm time
 * @param current_time the current time
 * @return true if the alarm time is equal to the current time, false otherwise
*/
bool check_alarm(struct dt alarm_time, struct dt current_time);

/**
 * Read alarm value from EEPROM storage
 * 
 * Reads alarm value from EEPROM storage.
 * @return the alarm value structure
*/
struct dt read_alarm();

/**
 * Remove alarm
 * 
 * Removes the alarm value from EEPROM storage.
*/
void remove_alarm();


/**
 * Alarm
 * 
 * Display blinking and playing sound.
 * @param melody the melody to play
*/
void alarm(struct melody melody);

/**
 * Snooze
 * 
 * Snooze alarm to new time 
 * @param alarm_time new alarm time 
*/
void snooze_alarm(struct dt alarm_time);

#endif