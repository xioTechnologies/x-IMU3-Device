/**
 * @file Ximu3SettingsJson.c
 * @author Seb Madgwick
 * @brief x-IMU3 settings JSON.
 */

//------------------------------------------------------------------------------
// Includes

#include "KeyCompare.h"
#include "Metadata.h"
#include <stdio.h>
#include <string.h>
#include "Ximu3Settings.h"
#include "Ximu3SettingsJson.h"

//------------------------------------------------------------------------------
// Function declarations

static void Append(char* const destination, const size_t destinationSize, const char* const string);
static JsonResult ParseBool(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly);
static JsonResult ParseCharArray(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly);
static JsonResult ParseFloat(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly);
static JsonResult ParseUint32(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Gets the index.
 * @param settings Settings.
 * @param index_ Index.
 * @param key Key.
 * @return Result.
 */
Ximu3Result Ximu3SettingsJsonGetIndex(Ximu3Settings * const settings, Ximu3SettingsIndex * const index_, const char* const key) {
    for (int index = 0; index < XIMU3_NUMBER_OF_SETTINGS; index++) {
        if (KeyCompare(key, MetadataGet(settings, index).key)) {
            *index_ = index;
            return Ximu3ResultOk;
        }
    }
    return Ximu3ResultError;
}

/**
 * @brief Gets the key.
 * @param settings Settings.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param index Index.
 */
void Ximu3SettingsJsonGetKey(Ximu3Settings * const settings, char* const destination, const size_t destinationSize, const Ximu3SettingsIndex index) {
    snprintf(destination, destinationSize, "%s", MetadataGet(settings, index).key);
}

/**
 * @brief Gets the value.
 * @param settings Settings.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param index Index.
 */
void Ximu3SettingsJsonGetValue(Ximu3Settings * const settings, char* const destination, const size_t destinationSize, const Ximu3SettingsIndex index) {

    // Get metadata
    const Metadata metadata = MetadataGet(settings, index);

    // Write value
    switch (metadata.type) {
        case MetadataTypeBool:
            snprintf(destination, destinationSize, "%s", *(bool*) metadata.value ? "true" : "false");
            break;
        case MetadataTypeCharArray:
            snprintf(destination, destinationSize, "\"%s\"", (char*) metadata.value);
            break;
        case MetadataTypeFloat:
            snprintf(destination, destinationSize, "%f", *(float*) metadata.value);
            break;
        case MetadataTypeUint32:
            snprintf(destination, destinationSize, "%u", *(uint32_t*) metadata.value);
            break;
    }
}

/**
 * @brief Gets the object.
 * @param settings Settings.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param index Index.
 */
void Ximu3SettingsJsonGetObject(Ximu3Settings * const settings, char* const destination, const size_t destinationSize, const Ximu3SettingsIndex index) {
    const Metadata metadata = MetadataGet(settings, index);
    char value[XIMU3_VALUE_SIZE];
    Ximu3SettingsJsonGetValue(settings, value, sizeof (value), index);
    snprintf(destination, destinationSize, "{\"%s\":%s}", metadata.key, value);
}

/**
 * @brief Gets all settings as a single object.
 * @param settings Settings.
 * @param destination Destination.
 * @param destinationSize Destination size.
 */
void Ximu3SettingsJsonGetObjectAll(Ximu3Settings * const settings, char* const destination, const size_t destinationSize) {

    // Object start
    snprintf(destination, destinationSize, "{\n");

    // Key/value pairs
    for (int index = 0; index < XIMU3_NUMBER_OF_SETTINGS; index++) {

        // Get metadata
        const Metadata metadata = MetadataGet(settings, index);

        // Indentation
        Append(destination, destinationSize, "    ");

        // Key
        char key[XIMU3_KEY_SIZE];
        snprintf(key, sizeof (key), "\"%s\"", metadata.name);

        // Value
        char value[XIMU3_VALUE_SIZE];
        Ximu3SettingsJsonGetValue(settings, value, sizeof (value), index);

        // Key/value pair
        const size_t stringLength = strlen(destination);
        snprintf(&destination[stringLength], destinationSize - stringLength, "%-*s : %s", XIMU3_MAX_KEY_LENGTH + 2, key, value); // 2 extra characters for quotation marks

        // Comma
        if (index < (XIMU3_NUMBER_OF_SETTINGS - 1)) {
            Append(destination, destinationSize, ",");
        }
        Append(destination, destinationSize, "\n");
    }

    // Object end
    Append(destination, destinationSize, "}\n");
}

/**
 * @brief Appends string.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param string String.
 */
static void Append(char* const destination, const size_t destinationSize, const char* const string) {
    const size_t stringLength = strlen(destination);
    snprintf(&destination[stringLength], destinationSize - stringLength, "%s", string);
}

/**
 * @brief Sets the value from a key/value pair.
 * @param settings Settings.
 * @param key Key.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 * @return Result.
 */
JsonResult Ximu3SettingsJsonSetKeyValue(Ximu3Settings * const settings, const char* const key, const char* * const value, const bool overrideReadOnly) {

    // Get index
    Ximu3SettingsIndex index;
    if (Ximu3SettingsJsonGetIndex(settings, &index, key) != 0) {
        return JsonResultOk;
    }

    // Get metadata
    const Metadata metadata = MetadataGet(settings, index);

    // Parse value
    switch (metadata.type) {
        case MetadataTypeBool:
            return ParseBool(settings, index, value, overrideReadOnly);
        case MetadataTypeCharArray:
            return ParseCharArray(settings, index, value, overrideReadOnly);
        case MetadataTypeFloat:
            return ParseFloat(settings, index, value, overrideReadOnly);
        case MetadataTypeUint32:
            return ParseUint32(settings, index, value, overrideReadOnly);
    }
    return JsonResultOk; // avoid compiler warning
}

/**
 * @brief Parse value representing a bool.
 * @param settings Settings.
 * @param index Index.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 * @return Result.
 */
static JsonResult ParseBool(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly) {
    bool boolean;
    const JsonResult result = JsonParseBoolean(value, &boolean);
    if (result != JsonResultOk) {
        return result;
    }
    Ximu3SettingsSet(settings, index, &boolean, overrideReadOnly);
    return JsonResultOk;
}

/**
 * @brief Parse value representing a char array.
 * @param settings Settings.
 * @param index Index.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 * @return Result.
 */
static JsonResult ParseCharArray(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly) {
    char string[XIMU3_VALUE_SIZE];
    const JsonResult result = JsonParseString(value, string, sizeof (string), NULL);
    if (result != JsonResultOk) {
        return result;
    }
    Ximu3SettingsSet(settings, index, string, overrideReadOnly);
    return JsonResultOk;
}

/**
 * @brief Parse value representing a float.
 * @param settings Settings.
 * @param index Index.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 * @return Result.
 */
static JsonResult ParseFloat(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly) {
    float number;
    const JsonResult result = JsonParseNumber(value, &number);
    if (result != JsonResultOk) {
        return result;
    }
    Ximu3SettingsSet(settings, index, &number, overrideReadOnly);
    return JsonResultOk;
}

/**
 * @brief Parse value representing a uint32_t.
 * @param settings Settings.
 * @param index Index.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 * @return Result.
 */
static JsonResult ParseUint32(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const char* * const value, const bool overrideReadOnly) {
    float numberFloat;
    const JsonResult result = JsonParseNumber(value, &numberFloat);
    if (result != JsonResultOk) {
        return result;
    }
    const uint32_t numberUint32 = (uint32_t) numberFloat;
    Ximu3SettingsSet(settings, index, &numberUint32, overrideReadOnly);
    return JsonResultOk;
}

/**
 * @brief Sets the values from an object.
 * @param settings Settings.
 * @param object_ Object.
 * @param overrideReadOnly True to override read-only.
 * @return Result.
 */
JsonResult Ximu3SettingsJsonSetObject(Ximu3Settings * const settings, const char* object_, const bool overrideReadOnly) {

    // Parse object start
    const char* * const object = &object_;
    JsonResult result = JsonParseObjectStart(object);
    if (result != JsonResultOk) {
        return result;
    }

    // Parse object end
    result = JsonParseObjectEnd(object);
    if (result == JsonResultOk) {
        return JsonResultOk;
    }

    // Loop through each key/value pair
    while (true) {

        // Parse key
        char key[XIMU3_KEY_SIZE];
        result = JsonParseKey(object, key, sizeof (key));
        if (result != JsonResultOk) {
            return result;
        }

        // Parse value
        result = Ximu3SettingsJsonSetKeyValue(settings, key, object, overrideReadOnly);
        if (result != JsonResultOk) {
            return result;
        }

        // Parse comma
        result = JsonParseComma(object);
        if (result == JsonResultOk) {
            continue;
        }

        // Parse object end
        result = JsonParseObjectEnd(object);
        if (result != JsonResultOk) {
            return result;
        }
        break;
    }
    return JsonResultOk;
}

//------------------------------------------------------------------------------
// End of file
