# DS18B20 Digital Temperature Sensor Driver for RP2040
This driver allows the the RP2040 MCU to interface with the DS18B20 temperature sensor using the RP2040's PIO. Once the DS18B20 has been initialized, a temperature can be read in either degrees Celsius or Fahrenheit.

#
 Note that CRC is not implemented to verify integrity of data retrieved from the DS18B20. This driver also only works with one device connected to the 1-Wire bus.
#

## Requirements
- RP2040 MCU (Raspberry Pi Pico)
- Pico SDK
- DS18B20 Digital Temperature Sensor
- Properly assembled 1-wire bus (More info: https://cdn-shop.adafruit.com/datasheets/DS18B20.pdf)

## How to use
This driver does not communicate with the DS18B20 by bit-banging. Rather, one of the RP2040's PIO state machines is used. As such, PIO assembly is required to program the state machine. You can read more about the RP2040's PIO in the RP2040 datasheet. For this driver, the assembly is included in a pre-generated C header file (ds18b20.pio.h). However, if you want to directly modify the ds18b20.pio file, it can be found in /pio. In this case, you must add the following line in you CMakeLists.txt file, assuming ds18b20.pio is in the same directory as your cmake list file, so that PIOASM can generate the C header file:
```
pico_generate_pio_header(ds18b20 ${CMAKE_CURRENT_LIST_DIR}/ds18b20.pio)
```

Before the temperature can be read, the PIO which will communicate with the DS18B20 must be initialized as follows:
```
int sm = ds18b20_init(pio0, ONE_WIRE_GPIO);
```
where ```ONE_WIRE_GPIO``` is defined as some GPIO pin connected to your 1-Wire bus.
This function will return the index of the state machine being used on your specified PIO. If a state machine could not be reserved, -1 is returned.  
  
Once the initialization is finished and you have a valid SM index, the temperature can be read as follows:
```
int8_t t = ds18b20_get_temperature(pio0, sm, MEASURE_IN_FAHRENHEIT);
```
where the temperature is returned as an 8-bit signed integer. ```sm``` is the index returned from ```ds18b20_init```. The third argument should be 1 if you want the temperature to be converted to Fahrenheit. If 0, it will be left in Celsius.

# Credit
This is heavily based on the text from:   
 https://www.i-programmer.info/programming/hardware/14527-the-pico-in-c-a-1-wire-pio-program.html