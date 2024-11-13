/**
 * List of available states.
 */
enum state {
    ALARM,
    CLOCK_AND_DATE,
    SHOW_ENV,
    MENU,
    ALARM_TRIGGERED,
    FACTORY_RESET
};


/**
 * Individual implementation of states.
 */

enum state state_clock_and_date();
enum state state_menu();
enum state state_alarm();
enum state state_show_env();
enum state state_alarm_triggered();
enum state state_factory_reset();