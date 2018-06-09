cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME firmware)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH firmware.ino)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src )
include(${CMAKE_SOURCE_DIR}/SoftSynth.cpp ${CMAKE_SOURCE_DIR}/SoftSynth.h)

#### Uncomment below additional settings as needed.
# set(${CMAKE_PROJECT_NAME}_BOARD mega)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)

set(test_SRCS SoftSynth.cpp)
set(test_HDRS SoftSynth.h)
set(test_BOARD nano)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
