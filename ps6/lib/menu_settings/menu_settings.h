#ifndef _MENU_SETTINGS_H
#define _MENU_SETTINGS_H
#include <Arduino.h>

/**
 * Print menu setting on the LCD display
 *
 * Prints menu setting on the LCD display at given position.
 * @param i the setting to print
 * @return true if setting is successful, false otherwise
 */

byte menu_setting(byte index);

/**
 * Setup menu on the LCD display
 *
 * Sets up menu on the LCD display.
 */

void menu_setup();

/**
 * Setup time on the LCD display
 *
 * Sets up time on the LCD display.
 * @return true if setup is successful, false otherwise
 
 */
void setup_time();

/**
 * Setup date on the LCD display
 *
 * Sets up date on the LCD display.
 */

void setup_date();

/**
 * Setup alarm on the LCD display
 *
 * Sets up alarm on the LCD display.
 */

void setup_alarm();

/**
 * Dismiss alarm on the LCD display
 *
 * Dismisses alarm on the LCD display.
 */

void dismiss_alarm();

#endif