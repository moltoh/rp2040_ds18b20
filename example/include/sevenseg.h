#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

void sevenseg_init(bool common_cathode);

void sevenseg_show(uint8_t val);

#endif