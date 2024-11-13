#include <Arduino.h>
#include "../../include/rtc_wrapper.h"
#include "date_time_setup.h"
/**
 * @brief Prints formatted string (including floating point variables) to serial line.
 *
 * @tparam T
 * @param str format string
 * @param args list of arguments to print
 */
template <typename... T>
void print(const char *str, T... args);

/**
 * @brief Prints DateTime structure to serial line.
 *
 * @param datetime date and time to print 
 */
void print_date_time(const dt &datetime);

/**
 * @brief Prints temperature and humidity to serial line.
 */

void print_temperature_humidity();

/**
 * @brief Prints number to lcd screen.
 *
 * @param number number to print
 */

void print_number(int number);

/**
 * @brief Prints alarm value to lcd screen.
 *
 * @param alarm_value alarm value to print
 * @param indicator flag to indicate which part of the alarm value is being set
 */

void print_alarm_value(void *alarm_value, enum flag indicator);

/**
 * Print cursor on the LCD display
 *
 * Prints cursor on the LCD display at given position.
 * @param x the x coordinate
 * @param y the y coordinate
 */

void print_cursor(int x, int y);

/**
 * Print menu on the LCD display
 *
 * Prints menu on the LCD display at given position.
 * @param first_element the first element of the menu
 * @param second_element the second element of the menu
 */

void print_menu(char* first_element, char* second_element);

/**
 * Print alarm value 
 * 
 * Prints the alarm value to the LCD screen.
 * @param alarm_value the alarm value
*/
void print_alarm();


