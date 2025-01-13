/**
* @file main.c
 * @author Seb Madgwick
 * @brief Test.
 */

//------------------------------------------------------------------------------
// Includes

#include "Ximu3Command.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
// Function declarations

static size_t Read(void *const destination, size_t numberOfBytes);

static void Write(const void *const data, const size_t numberOfBytes);

static void Ping(const char * *const value, Ximu3CommandResponse *const response);

//------------------------------------------------------------------------------
// Variables

static Ximu3CommandInterface interfaces[] = {
    {
        .name = "USB",
        .read = Read,
        .write = Write,
    },
};
static const Ximu3CommandMap commands[] = {
    {"ping", Ping},
};
static Ximu3CommandBridge bridge = {
    .interfaces = interfaces,
    .numberOfInterfaces = sizeof (interfaces) / sizeof(Ximu3CommandInterface),
    .commands = commands,
    .numberOfCommands = sizeof (commands) / sizeof(Ximu3CommandMap),
};
static char buffer[256] = {0};

//------------------------------------------------------------------------------
// Functions

int main(void) {
    strcpy(buffer, "{\"ping\":null}\n");
    Ximu3CommandTasks(&bridge);

    return EXIT_SUCCESS;
}

static size_t Read(void *const destination, size_t numberOfBytes) {
    strncpy(destination, buffer, numberOfBytes);
    strcpy(buffer, "");
    return strlen(destination);;
}

static void Write(const void *const data, const size_t numberOfBytes) {
    char string[256] = {0};
    memcpy(string, data, numberOfBytes);
    printf("%s", string);
}

static void Ping(const char * *const value, Ximu3CommandResponse *const response) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    Ximu3CommandRespondPing(response, "x-IMU3", "01234567");
}

//------------------------------------------------------------------------------
// End of file
