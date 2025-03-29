/**
 * @file main.c
 * @author Seb Madgwick
 * @brief Simple example and test.
 */

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ximu3Command.h"

//------------------------------------------------------------------------------
// Function declarations

static size_t UsbRead(void *const destination, size_t numberOfBytes);

static void UsbWrite(const void *const data, const size_t numberOfBytes);

static void NvmRead(uint32_t address, void *const destination, size_t numberOfBytes);

static void NvmWrite(const uint32_t address, const void *const data, const size_t numberOfBytes);

static void InitialiseEpilogue(void);

static void DefaultsEpilogue(void);

static bool OverrideReadOnly(void);

static void WriteEpilogue(const Ximu3SettingsIndex index);

static void Error(const char *const error);

static void Ping(const char * *const value, Ximu3CommandResponse *const response);

static void Factory(const char * *const value, Ximu3CommandResponse *const response);

static void Shutdown(const char * *const value, Ximu3CommandResponse *const response);

//------------------------------------------------------------------------------
// Variables

static Ximu3CommandInterface interfaces[] = {
    {
        .name = "USB",
        .read = UsbRead,
        .write = UsbWrite,
    },
};

static const Ximu3CommandMap commands[] = {
    {"ping", Ping},
    {"factory", Factory},
    {"shutdown", Shutdown},
};

static Ximu3Settings settings = {
    .nvmStartAddress = 0,
    .nvmRead = NvmRead,
    .nvmWrite = NvmWrite,
    .initialiseEpilogue = InitialiseEpilogue,
    .defaultsEpilogue = DefaultsEpilogue,
};

static Ximu3CommandBridge bridge = {
    .interfaces = interfaces,
    .numberOfInterfaces = sizeof (interfaces) / sizeof(Ximu3CommandInterface),
    .commands = commands,
    .numberOfCommands = sizeof (commands) / sizeof(Ximu3CommandMap),
    .settings = &settings,
    .overrideReadOnly = OverrideReadOnly,
    .writeEpilogue = WriteEpilogue,
    .error = Error,
};

static uint8_t nvmMemory[1024];

static const char firmwareVersion[] = "v1.0.0";

static bool factoryMode;

static volatile bool shutdown;

//------------------------------------------------------------------------------
// Functions

int main(void) {
    memset(nvmMemory, 0xFF, sizeof(nvmMemory));

    Ximu3SettingsInitialise(&settings);

    while (shutdown == false) {
        Ximu3CommandTasks(&bridge);
    }

    return EXIT_SUCCESS;
}

static size_t UsbRead(void *const destination, size_t numberOfBytes) {
    static const char *messages[] = {
        "\n",
        "{\"a\"\n",
        "{\"b\":\n",
        "{\"a\":0,\n",
        "{\"ping\":null}\n",
        "{\"firmware_version\":null}\n",
        "{\"calibration_date\":\"Today\"}\n", /* invalid write of read-only setting */
        "{\"factory\":null}\n",
        "{\"calibration_date\":\"Today\"}\n", /* valid write read-only setting in factory mode */
        "{\"garbage\":null}\n",
        "{\"shutdown\":null}\n",
        NULL,
    };
    static int index;

    if (messages[index] == NULL) {
        return 0;
    }

    const size_t messageLength = strlen(messages[index]);

    if (messageLength > numberOfBytes) {
        return 0;
    }

    strncpy(destination, messages[index++], numberOfBytes);
    return messageLength;
}

static void UsbWrite(const void *const data, const size_t numberOfBytes) {
    fwrite(data, 1, numberOfBytes, stdout);
    fflush(stdout);
}

static void NvmRead(uint32_t address, void *const destination, size_t numberOfBytes) {
    memcpy(destination, &nvmMemory[address], numberOfBytes);
}

static void NvmWrite(const uint32_t address, const void *const data, const size_t numberOfBytes) {
    memcpy(&nvmMemory[address], (void *) data, numberOfBytes);
}

static void InitialiseEpilogue(void) {
    if (strncmp(Ximu3SettingsGet(&settings)->firmwareVersion, firmwareVersion, sizeof (firmwareVersion)) != 0) {
        Ximu3SettingsDefaults(&settings, false);
    }
}

static void DefaultsEpilogue(void) {
    Ximu3SettingsSet(&settings, Ximu3SettingsIndexSerialNumber, "01234567", true);
    Ximu3SettingsSet(&settings, Ximu3SettingsIndexFirmwareVersion, "v1.0.0", true);
}

static bool OverrideReadOnly(void) {
    return factoryMode;
}

static void WriteEpilogue(const Ximu3SettingsIndex index) {
    (void) index; // avoid compiler warning
    Ximu3SettingsSave(&settings);
}

static void Error(const char *const error) {
    printf("Error: %s\n", error);
    fflush(stdout);
}

static void Ping(const char * *const value, Ximu3CommandResponse *const response) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    Ximu3CommandRespondPing(response, Ximu3SettingsGet(&settings)->deviceName, Ximu3SettingsGet(&settings)->serialNumber);
}

static void Factory(const char * *const value, Ximu3CommandResponse *const response) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    factoryMode = true;
    Ximu3CommandRespond(response);
}

static void Shutdown(const char * *const value, Ximu3CommandResponse *const response) {
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    shutdown = true;
    Ximu3CommandRespond(response);
}

//------------------------------------------------------------------------------
// End of file
