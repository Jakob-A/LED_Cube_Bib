cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME LED_Cube_Bib)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH LED_Cube_Bib.ino)

#### Uncomment below additional settings as needed.
# set(${CMAKE_PROJECT_NAME}_BOARD mega)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})

add_executable(LED_RaspCupe
        LEDCube.h
        LEDCube.cpp
        CubeEffects.cpp
        CubeEffects.h
        CubeText.cpp
        CubeText.h
        DrawFunctions.cpp
        DrawFunctions.h)