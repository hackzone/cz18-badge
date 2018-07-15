cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME firmware)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH firmware.ino)

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD nano)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
set(nano.build.mcu atmega328p)
set(nano.upload.speed 115200)

set(${CMAKE_PROJECT_NAME}_SRCS common.cpp buttons.cpp eeprom.cpp firmware.ino )
set(${CMAKE_PROJECT_NAME}_HDRS common.h buttons.h eeprom.h)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
