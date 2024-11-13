#ifndef _DATE_TIME_SETUP_H
#define _DATE_TIME_SETUP_H
#include <Arduino.h>


/**
 * @brief Enum flag
 *
 * Enum flag to indicate, which parameter we want to change.
 */

enum flag {
    HOURS,
    MINUTES,
    SECONDS,
    DAY,
    MONTH,
    YEAR
};

/**
 * @brief Configure time and date
 *
 * Configures time and date.
 * @param value the value to configure
 * @param indicator the indicator to configure
 * @return true if configuration is successful, false otherwise
 */

bool configure_time_and_date(void *value, enum flag indicator);

/**
 * @brief Print value
 *
 * Prints value.
 * @param value the value to print
 * @param indicator the indicator to print
 */
void print_value(void *value, enum flag indicator);

/**
 * @brief Days in month
 *
 * Returns number of days in month.
 * @param month the month
 * @param year the year
 * @return number of days in month
 */

byte days_in_month(byte month, int year);

#endif