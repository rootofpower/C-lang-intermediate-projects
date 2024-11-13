#include "rtc_wrapper.h"
#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(4, 5, 9); // DAT, CLK, RST
RtcDS1302<ThreeWire> Rtc(myWire);

void clock_init(){
    // set time and date
    Rtc.Begin();
}

void set_date(const byte day, const byte month, const int year){
    RtcDateTime current = Rtc.GetDateTime();
    RtcDateTime new_date = RtcDateTime(year, month, day, current.Hour(), current.Minute(), current.Second());
    Rtc.SetDateTime(new_date);
}

void set_time(const byte hours, const byte minutes, const byte seconds){
    RtcDateTime current = Rtc.GetDateTime();
    RtcDateTime new_time = RtcDateTime(current.Year(), current.Month(), current.Day(), hours, minutes, seconds);
    Rtc.SetDateTime(new_time);
}

void set_datetime(const byte day, const byte month, const int year, const byte hours, const byte minutes, const byte seconds){
    RtcDateTime new_time = RtcDateTime(year, month, day, hours, minutes, seconds);
    Rtc.SetDateTime(new_time);
}

byte get_day(){
    RtcDateTime current = Rtc.GetDateTime();
    return current.Day();
}

byte get_month(){
    RtcDateTime current = Rtc.GetDateTime();
    return current.Month();
}

int get_year(){
    RtcDateTime current = Rtc.GetDateTime();
    return current.Year();
}

byte get_hours(){
    RtcDateTime current = Rtc.GetDateTime();
    return current.Hour();
}

byte get_minutes(){
    RtcDateTime current = Rtc.GetDateTime();
    return current.Minute();
}

byte get_seconds(){
    RtcDateTime current = Rtc.GetDateTime();
    return current.Second();
}


struct dt now(){
    RtcDateTime now = Rtc.GetDateTime();
    struct dt current_time = {
        now.Day(),
        now.Month(),
        now.Year(),
        now.Hour(),
        now.Minute(),
        now.Second()
    };

    return current_time;
}