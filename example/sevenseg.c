#include "pico/stdlib.h"
#include "sevenseg.h"

#define SEVENSEG_GPIO_PINS 0x3FFF

const uint32_t INT_GPIO_MAP[] = {
    0b1101111,  // 0
    0b0101000,  // 1
    0b1011101,  // 2
    0b1111001,  // 3
    0b0111010,  // 4
    0b1110011,  // 5
    0b1110111,  // 6
    0b0101001,  // 7
    0b1111111,  // 8
    0b1111011   // 9
};

/**
 * @brief Initilizes GPIO pins 0 through 13 for two seven-segment displays. 
 * Will turn on center segments of both displays once initilized.
 * 
 * @param common_cathode True if the displays are common cathode, false if common anode. 
 */
void sevenseg_init(bool common_cathode) {
    gpio_init_mask(SEVENSEG_GPIO_PINS);
    gpio_set_dir_out_masked(SEVENSEG_GPIO_PINS);
    
    if (!common_cathode) 
        _invert_gpio();

    gpio_put_masked(0x3FFF, 0x810);
}

/**
 * @brief Displays a two-digit value (0-99) on the two seven-segment displays. 
 * Must be called after sevenseg_init().
 * 
 * @param val The value to display (0-99).
 */
void sevenseg_show(uint8_t val) {
    gpio_clr_mask(SEVENSEG_GPIO_PINS);

    bool too_big = val > 99;

    uint32_t lsd_mask = INT_GPIO_MAP[too_big ? 9 : val % 10];
    uint32_t msd_mask = INT_GPIO_MAP[too_big ? 9 : val / 10];
    
    gpio_put_masked(SEVENSEG_GPIO_PINS, (msd_mask << 7) | lsd_mask);
}

void _invert_gpio() {
    for (uint8_t i = 0; i < 14; i++) {
        gpio_set_outover(i, GPIO_OVERRIDE_INVERT);
    }
}
