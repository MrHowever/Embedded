cmake_minimum_required(VERSION 3.15)
project(RaspberryPi C)

set(CMAKE_C_STANDARD 11)

add_executable(RaspberryPi
        LightSensor/light.c
        buzzer.c
        expander.c
        humidity.c LightSensor/light.h controller.h controller.c adc.h adc.c humidity.h expander.h buzzer.h main.c)
