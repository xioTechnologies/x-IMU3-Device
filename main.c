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
#include "Ximu3.h"

//------------------------------------------------------------------------------
// Function declarations

static size_t UsbRead(void *const destination, size_t numberOfBytes, void *const context);

static void UsbWrite(const void *const data, const size_t numberOfBytes, void *const context);

static void NvmRead(void *const destination, size_t numberOfBytes, void *const context);

static void NvmWrite(const void *const data, const size_t numberOfBytes, void *const context);

static void InitialiseEpilogue(void *const context);

static void DefaultsEpilogue(void *const context);

static bool OverrideReadOnly(void *const context);

static void WriteEpilogue(const Ximu3SettingsIndex index, void *const context);

static void Error(const char *const error, void *const context);

static void Ping(const char * *const value, Ximu3CommandResponse *const response, void *const context);

static void Factory(const char * *const value, Ximu3CommandResponse *const response, void *const context);

static void Shutdown(const char * *const value, Ximu3CommandResponse *const response, void *const context);

//------------------------------------------------------------------------------
// Variables

static Ximu3CommandInterface interfaces[] = {
    {.name = "USB", .read = UsbRead, .write = UsbWrite},
};

static const Ximu3CommandMap commands[] = {
    {"ping", Ping},
    {"factory", Factory},
    {"shutdown", Shutdown},
};

static Ximu3Settings settings = {
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

static size_t UsbRead(void *const destination, size_t numberOfBytes, void *const context) {
    (void) context; // avoid compiler warning
    static const char *messages[] = {
        "\n",
        "{\"a\"\n",
        "{\"b\":\n",
        "{\"a\":0,\"b\":0}\n",
        "{\"garbage\":null}\n",
        "{\"ping\":null}\n",
        "{\"firmware_version\":null}\n",
        "{\"hardware_version\":null}\n",
        "{\"hardware_version\":\"v1.0.0\"}\n", /* invalid write of read-only setting */
        "{\"factory\":null}\n",
        "{\"hardware_version\":\"v1.0.0\"}\n", /* valid write read-only setting in factory mode */
        "{\"enumerate_0\":null}\n",
        "{\"enumerate_1\":null}\n",
        "{\"enumerate_2\":null}\n",
        "{\"enumerate_999\":null}\n",
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

static void UsbWrite(const void *const data, const size_t numberOfBytes, void *const context) {
    (void) context; // avoid compiler warning
    fwrite(data, 1, numberOfBytes, stdout);
    fflush(stdout);
}

static void NvmRead(void *const destination, size_t numberOfBytes, void *const context) {
    (void) context; // avoid compiler warning
    memcpy(destination, &nvmMemory, numberOfBytes);
}

static void NvmWrite(const void *const data, const size_t numberOfBytes, void *const context) {
    (void) context; // avoid compiler warning
    memcpy(&nvmMemory, (void *) data, numberOfBytes);
}

static void InitialiseEpilogue(void *const context) {
    (void) context; // avoid compiler warning
    const char *const nvmFirmwareVersion = Ximu3SettingsGet(&settings)->firmwareVersion;
    if (strspn(nvmFirmwareVersion, "?") == strlen(nvmFirmwareVersion)) {
        Ximu3SettingsDefaults(&settings, true); // load defaults if NVM blank
    }
}

static void DefaultsEpilogue(void *const context) {
    (void) context; // avoid compiler warning
    Ximu3SettingsSet(&settings, Ximu3SettingsIndexSerialNumber, "01234567", true);
    Ximu3SettingsSet(&settings, Ximu3SettingsIndexFirmwareVersion, "v1.0.0", true);
}

static bool OverrideReadOnly(void *const context) {
    (void) context; // avoid compiler warning
    return factoryMode;
}

static void WriteEpilogue(const Ximu3SettingsIndex index, void *const context) {
    (void) index; // avoid compiler warning
    (void) context; // avoid compiler warning
    Ximu3SettingsSave(&settings);
}

static void Error(const char *const error, void *const context) {
    (void) context; // avoid compiler warning
    printf("Error: %s\n", error);
    fflush(stdout);
}

static void Ping(const char * *const value, Ximu3CommandResponse *const response, void *const context) {
    (void) context; // avoid compiler warning
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    Ximu3CommandRespondPing(response, Ximu3SettingsGet(&settings)->deviceName, Ximu3SettingsGet(&settings)->serialNumber);
}

static void Factory(const char * *const value, Ximu3CommandResponse *const response, void *const context) {
    (void) context; // avoid compiler warning
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    factoryMode = true;
    Ximu3CommandRespond(response);
}

static void Shutdown(const char * *const value, Ximu3CommandResponse *const response, void *const context) {
    (void) context; // avoid compiler warning
    if (Ximu3CommandParseNull(value, response) != 0) {
        return;
    }
    shutdown = true;
    Ximu3CommandRespond(response);
}

//------------------------------------------------------------------------------
// End of file
