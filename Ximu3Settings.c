/**
 * @file Ximu3Settings.c
 * @author Seb Madgwick
 * @brief x-IMU3 settings.
 */

//------------------------------------------------------------------------------
// Includes

#include <ctype.h>
#include "Metadata.h"
#include <string.h>
#include "Ximu3Settings.h"

//------------------------------------------------------------------------------
// Function declarations

static void WriteString(char* const destination, const size_t destinationSize, const char* string);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises the module.  This function must only be called once, on
 * system startup.
 * @param settings Settings.
 */
void Ximu3SettingsInitialise(Ximu3Settings * const settings) {

    // Read values from NVM
    Ximu3SettingsValues blank;
    memset(&blank, 0xFF, sizeof (blank));
    settings->values = blank;
    if (settings->nvmRead != NULL) {
        settings->nvmRead(settings->nvmStartAddress, &settings->values, sizeof (settings->values));
    }

    // Load defaults if NVM blank
    if (memcmp(&settings->values, &blank, sizeof (settings->values)) == 0) {
        Ximu3SettingsDefaults(settings, true);
    }

    // Epilogue
    if (settings->initialiseEpilogue != NULL) {
        settings->initialiseEpilogue();
    }
}

/**
 * @brief Loads defaults.
 * @param settings Settings.
 * @param overwriteCalibration True to overwrite calibration.
 */
void Ximu3SettingsDefaults(Ximu3Settings * const settings, const bool overwriteCalibration) {

    // Loads defaults
    for (size_t index = 0; index < XIMU3_NUMBER_OF_SETTINGS; index++) {
        const Metadata metadata = MetadataGet(settings, index);
        if (metadata.calibration && (overwriteCalibration == false)) {
            continue;
        }
        Ximu3SettingsSet(settings, index, metadata.defaultValue, true);
    }

    // Epilogue
    if (settings->defaultsEpilogue != NULL) {
        settings->defaultsEpilogue();
    }
}

/**
 * @brief Returns values.
 * @return Values.
 */
const Ximu3SettingsValues* Ximu3SettingsGet(Ximu3Settings * const settings) {
    return &settings->values;
}

/**
 * @brief Sets value.
 * @param settings Settings.
 * @param index Index.
 * @param value Value.
 * @param overrideReadOnly True to override read-only.
 */
void Ximu3SettingsSet(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const void* const value, const bool overrideReadOnly) {

    // Get metadata
    const Metadata metadata = MetadataGet(settings, index);

    // Do nothing if read-only
    if ((overrideReadOnly == false) && metadata.readOnly) {
        return;
    }

    // Do nothing if value unchanged
    if ((metadata.type == MetadataTypeCharArray) && (strncmp(metadata.value, value, metadata.size) == 0)) {
        return;
    } else if (memcmp(metadata.value, value, metadata.size) == 0) {
        return;
    }

    // Set apply pending flag
    *metadata.applyPending = true;

    // Set value
    switch (metadata.type) {
        case MetadataTypeBool:
        case MetadataTypeFloat:
        case MetadataTypeUint32:
            memcpy(metadata.value, value, metadata.size);
            break;
        case MetadataTypeCharArray:
            WriteString(metadata.value, metadata.size, value);
            break;
    }
}

/**
 * @brief Writes string.  Unprintable characters are replaced with '?'.  The
 * destination is padded with trailing zeros.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param string String.
 */
static void WriteString(char* const destination, const size_t destinationSize, const char* string) {
    for (size_t index = 0; index < destinationSize; index++) {
        if (*string == '\0') {
            destination[index] = *string;
            continue;
        }
        if ((*string < 0) || (isprint(*string) == 0)) {
            destination[index] = '?';
        } else {
            destination[index] = *string;
        }
        string++;
    }
    destination[destinationSize - 1] = '\0';
}

/**
 * @brief Saves to NVM.
 * @param settings Settings.
 */
void Ximu3SettingsSave(Ximu3Settings * const settings) {
    if (settings->nvmWrite != NULL) {
        settings->nvmWrite(settings->nvmStartAddress, &settings->values, sizeof (settings->values));
    }
}

/**
 * @brief Returns true if apply pending.  Calling this function will reset the
 * flag.
 * @param settings Settings.
 * @param index Index.
 * @return True if apply pending.
 */
bool Ximu3SettingsApplyPending(Ximu3Settings * const settings, const Ximu3SettingsIndex index) {
    const Metadata metadata = MetadataGet(settings, index);
    const bool applyPending = *metadata.applyPending;
    *metadata.applyPending = false;
    return applyPending;
}

//------------------------------------------------------------------------------
// End of file
