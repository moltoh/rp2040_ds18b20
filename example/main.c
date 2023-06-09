#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/pio.h"
#include "sevenseg.h"
#include "ds18b20.h"

#define ONE_WIRE_GPIO 22
#define MEASURE_IN_FAHRENHEIT 1

int main() {
    stdio_init_all();
    sevenseg_init(false);

    int sm = ds18b20_init(pio0, ONE_WIRE_GPIO);
    int8_t t;

    while(1) {
        t = ds18b20_get_temperature(pio0, sm, MEASURE_IN_FAHRENHEIT);

        printf(
            "Temperature %d degrees %s\n", 
            t, 
            MEASURE_IN_FAHRENHEIT ? "fahrenheit" : "celsius"
        );

        sevenseg_show(t);

        sleep_ms(500);
    };
    
    return 0;
}