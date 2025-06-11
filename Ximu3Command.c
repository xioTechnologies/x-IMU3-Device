/**
 * @file Ximu3Command.c
 * @author Seb Madgwick
 * @brief x-IMU3 commands.
 */

//------------------------------------------------------------------------------
// Includes

#include "JSON/Json.h"
#include "KeyCompare.h"
#include "Metadata.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Ximu3Command.h"
#include "Ximu3SettingsJson.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Uncomment this line to enable printing of messages.
 */
//#define PRINT_MESSAGES

//------------------------------------------------------------------------------
// Function declarations

static void Receive(Ximu3CommandBridge * const bridge, Ximu3CommandInterface * const interface);
static void Parse(const Ximu3CommandBridge * const bridge, const Ximu3CommandInterface * const interface, const char* * const json);
static void Error(const Ximu3CommandBridge * const bridge, const char* format, ...);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Module tasks. This function should be called repeatedly within the
 * main program loop.
 * @param bridge Bridge.
 */
void Ximu3CommandTasks(Ximu3CommandBridge * const bridge) {
    for (int index = 0; index < bridge->numberOfInterfaces; index++) {
        Receive(bridge, &bridge->interfaces[index]);
    }
}

/**
 * @brief Receive data.
 * @param bridge Bridge.
 * @param interface Interface.
 */
static void Receive(Ximu3CommandBridge * const bridge, Ximu3CommandInterface * const interface) {
    while (true) {

        // Read data
        uint8_t data[XIMU3_OBJECT_SIZE];
        const size_t numberOfBytes = interface->read(data, sizeof (data), bridge->context);
        if (numberOfBytes == 0) {
            break;
        }

        // Process each byte
        for (size_t index = 0; index < numberOfBytes; index++) {

            // Add to buffer
            interface->buffer[interface->index] = data[index];

            // Parse if termination detected
            if (interface->buffer[interface->index] == '\n') {

                // Terminate string
                interface->buffer[interface->index] = '\0';

                // Parse command
                const char* json = interface->buffer;
                Parse(bridge, interface, &json);
                interface->index = 0;
                continue;
            }

            // Increment index
            if (++interface->index >= sizeof (interface->buffer)) {
                Error(bridge, "%s receive error. Buffer overrun.", interface->name);
                interface->index = 0;
                continue;
            }
        }
    }
}

/**
 * @brief Parse JSON as command.
 * @param bridge Bridge.
 * @param interface Interface.
 * @param json JSON.
 */
static void Parse(const Ximu3CommandBridge * const bridge, const Ximu3CommandInterface * const interface, const char* * const json) {
#ifdef PRINT_MESSAGES
    printf("%s RX %s\n", interface->name, interface->buffer);
#endif

    // Parse object start
    JsonResult result = JsonParseObjectStart(json);
    if (result != JsonResultOk) {
        Error(bridge, "%s receive error. Not a JSON object.", interface->name);
        return;
    }

    // Parse key
    char key[XIMU3_KEY_SIZE];
    result = JsonParseKey(json, key, sizeof (key));
    if (result != JsonResultOk) {
        Error(bridge, "%s receive error. Unable able to parse key. %s.", interface->name, JsonResultToString(result));
        return;
    }

    // Parse value
    const char* value = *json;
    result = JsonParse(json);
    if (result != JsonResultOk) {
        Error(bridge, "%s receive error. Unable able to parse value. %s.", interface->name, JsonResultToString(result));
        return;
    }

    // Parse object end
    result = JsonParseObjectEnd(json);
    if (result != JsonResultOk) {
        Error(bridge, "%s receive error. JSON object is not a single key/value pair.", interface->name);
        return;
    }

    // Initialise response
    Ximu3CommandResponse response = {.interface = interface, .value = "null", .context = bridge->context};
    snprintf(response.key, sizeof (response.key), "%s", key);

    // Commands
    for (int index = 0; index < bridge->numberOfCommands; index++) {
        if (KeyCompare(key, bridge->commands[index].key)) {
            bridge->commands[index].callback(&value, &response, bridge->context);
            return;
        }
    }

    // Settings
    if (bridge->settings != NULL) {
        Ximu3SettingsIndex index;
        if (Ximu3SettingsJsonGetIndex(bridge->settings, &index, key) == 0) {

            // Read
            if (JsonParseNull(&value) == JsonResultOk) {
                Ximu3SettingsJsonGetValue(bridge->settings, response.value, sizeof (response.value), index);
                Ximu3CommandRespond(&response);
                return;
            }

            // Write
            const Metadata metadata = MetadataGet(bridge->settings, index);
            const bool overrideReadOnly = bridge->overrideReadOnly == NULL ? false : bridge->overrideReadOnly(bridge->context);
            if (metadata.readOnly && (overrideReadOnly == false)) {
                Ximu3CommandRespondError(&response, "Read-only");
                return;
            }
            result = Ximu3SettingsJsonSetKeyValue(bridge->settings, key, &value, overrideReadOnly);
            if (result != JsonResultOk) {
                Ximu3CommandRespondError(&response, JsonResultToString(result));
                return;
            }
            if (bridge->writeEpilogue != NULL) {
                bridge->writeEpilogue(index, bridge->context);
            }
            Ximu3SettingsJsonGetValue(bridge->settings, response.value, sizeof (response.value), index);
            Ximu3CommandRespond(&response);
            return;
        }

        // Enumerate
        const char * keyPointer = key;
        if (KeyComparePartial(&keyPointer, "enumerate")) {
            int integer;
            if (sscanf(keyPointer, "%i", &integer) != 1) {
                Ximu3CommandRespondError(&response, "Unable to parse index");
                return;
            }
            if (Ximu3SettingsIndexFrom(&index, integer) != Ximu3ResultOk) {
                Ximu3CommandRespondError(&response, "Invalid index");
                return;
            }
            Ximu3SettingsJsonGetObject(bridge->settings, response.value, sizeof (response.value), integer);
            Ximu3CommandRespond(&response);
            return;
        }
    }

    // Unknown command
    if (bridge->unknown != NULL) {
        bridge->unknown(key, &value, &response, bridge->context);
        return;
    }
    Ximu3CommandRespondError(&response, "Unknown command");
}

/**
 * @brief Parses string and responds with error if unsuccessful.
 * @param value Value.
 * @param response Response.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param numberOfBytes Number of bytes in string. NULL if not required.
 * @return Result.
 */
Ximu3Result Ximu3CommandParseString(const char* * const value, Ximu3CommandResponse * const response, char* const destination, const size_t destinationSize, size_t * const numberOfBytes) {
    const JsonResult result = JsonParseString(value, destination, destinationSize, numberOfBytes);
    if (result != JsonResultOk) {
        Ximu3CommandRespondError(response, JsonResultToString(result));
        return Ximu3ResultError;
    }
    return Ximu3ResultOk;
}

/**
 * @brief Parses number and responds with error if unsuccessful.
 * @param value Value.
 * @param response Response.
 * @param number Number.
 * @return Result.
 */
Ximu3Result Ximu3CommandParseNumber(const char* * const value, Ximu3CommandResponse * const response, float *const number) {
    const JsonResult result = JsonParseNumber(value, number);
    if (result != JsonResultOk) {
        Ximu3CommandRespondError(response, JsonResultToString(result));
        return Ximu3ResultError;
    }
    return Ximu3ResultOk;
}

/**
 * @brief Parses boolean and responds with error if unsuccessful.
 * @param value Value.
 * @param response Response.
 * @param boolean Boolean.
 * @return Result.
 */
Ximu3Result Ximu3CommandParseBoolean(const char* * const value, Ximu3CommandResponse * const response, bool * const boolean) {
    const JsonResult result = JsonParseBoolean(value, boolean);
    if (result != JsonResultOk) {
        Ximu3CommandRespondError(response, JsonResultToString(result));
        return Ximu3ResultError;
    }
    return Ximu3ResultOk;
}

/**
 * @brief Parses null and responds with error if unsuccessful.
 * @param value Value.
 * @param response Response.
 * @return Result.
 */
Ximu3Result Ximu3CommandParseNull(const char* * const value, Ximu3CommandResponse * const response) {
    const JsonResult result = JsonParseNull(value);
    if (result != JsonResultOk) {
        Ximu3CommandRespondError(response, JsonResultToString(result));
        return Ximu3ResultError;
    }
    return Ximu3ResultOk;
}

/**
 * @brief Responds to command.
 * @param response Response.
 */
void Ximu3CommandRespond(Ximu3CommandResponse * const response) {
    char string[XIMU3_OBJECT_SIZE];
    snprintf(string, sizeof (string), "{\"%s\":%s}\n", response->key, response->value);
    response->interface->write(string, strlen(string), response->context);
#ifdef PRINT_MESSAGES
    printf("%s TX %s", response->interface->name, string);
#endif
}

/**
 * @brief Responds to ping command.
 * @param response Response.
 * @param name Name.
 * @param sn Serial number.
 */
void Ximu3CommandRespondPing(Ximu3CommandResponse * const response, const char* const name, const char* const sn) {
    snprintf(response->value, sizeof (response->value), "{\"interface\":\"%s\",\"name\":\"%s\",\"sn\":\"%s\"}", response->interface->name, name, sn);
    Ximu3CommandRespond(response);
}

/**
 * @brief Responds to command with error.
 * @param response Response.
 * @param error Error.
 */
void Ximu3CommandRespondError(Ximu3CommandResponse * const response, const char* const error) {
    snprintf(response->value, sizeof (response->value), "{\"error\":\"%s\"}", error);
    Ximu3CommandRespond(response);
}

/**
 * @param Error handler.
 * @param bridge Bridge.
 * @param format Format.
 * @param ...
 */
static void Error(const Ximu3CommandBridge * const bridge, const char* format, ...) {
    if (bridge->error == NULL) {
        return;
    }
    char string[256];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(string, sizeof (string), format, arguments);
    va_end(arguments);
    bridge->error(string, bridge->context);
}

//------------------------------------------------------------------------------
// End of file
