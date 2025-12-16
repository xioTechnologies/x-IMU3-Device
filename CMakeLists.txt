cmake_minimum_required(VERSION 3.15)
project(x-IMU3-Device)

add_executable(Test JSON/Json.c Key.c main.c Metadata.c Ximu3Command.c Ximu3Data.c Ximu3Definitions.c Ximu3Settings.c Ximu3SettingsJson.c)

if (MSVC)
    target_compile_options(Test PRIVATE /W4 /WX)
else ()
    target_compile_options(Test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif ()

add_definitions(-D_CRT_SECURE_NO_WARNINGS) # disable MSVC warnings for unsafe functions, e.g. sscanf
