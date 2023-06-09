cmake_minimum_required(VERSION 3.13)

include_directories(../ include)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(ds18b20)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(ds18b20 
    main.c
    sevenseg.c
    ../ds18b20.c
)

pico_enable_stdio_usb(ds18b20 1)
pico_enable_stdio_uart(ds18b20 0)

# by default the header is generated into the build dir
pico_generate_pio_header(ds18b20 ${CMAKE_CURRENT_LIST_DIR}/../pio/ds18b20.pio)
# however, alternatively you can choose to generate it somewhere else (in this case in the source tree for check in)
#pico_generate_pio_header(pio_blink ${CMAKE_CURRENT_LIST_DIR}/blink.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_sources(ds18b20 PRIVATE main.c)

target_link_libraries(ds18b20 PRIVATE pico_stdlib hardware_pio)

pico_add_extra_outputs(ds18b20)