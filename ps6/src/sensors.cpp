#include "sensors.h"
#include "config.h"
#include "DHT.h"

DHT dht(DHT_PIN, DHT11);

void sensors_init() {
    dht.begin();
}

float get_temperature() {
    return dht.readTemperature();
}

int get_humidity() {
    return dht.readHumidity();
}