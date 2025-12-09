cmake_minimum_required(VERSION 3.22)
set(BOARD nucleo_f411re)
find_package(Zephyr)
project(2gpio_2)

target_sources(app PRIVATE
    src/main.c
    src/esp8266_init.c
    src/my_dts_init.c
    src/uart1_handler.c
    src/thread_creation.c
)