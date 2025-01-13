/**
 * @file Ximu3Settings.h
 * @author Seb Madgwick
 * @brief x-IMU3 settings.
 */

#ifndef XIMU3_SETTINGS_H
#define XIMU3_SETTINGS_H

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Ximu3Definitions.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Settings.
 */
typedef struct {
    const int nvmStartAddress;
    void(*nvmRead)(const uint32_t address, void* const destination, size_t numberOfBytes); // NULL if unused
    void(*nvmWrite)(const uint32_t address, const void* const data, const size_t numberOfBytes); // NULL if unused
    void(*initialiseEpilogue)(void); // NULL if unused
    void(*defaultsEpilogue)(void); // NULL if unused

    // Private
    Ximu3SettingsValues values;
    bool applyPendings[XIMU3_NUMBER_OF_SETTINGS];
} Ximu3Settings;

//------------------------------------------------------------------------------
// Function declarations

void Ximu3SettingsInitialise(Ximu3Settings * const settings);
void Ximu3SettingsDefaults(Ximu3Settings * const settings, const bool overwriteCalibration);
const Ximu3SettingsValues* Ximu3SettingsGet(Ximu3Settings * const settings);
void Ximu3SettingsSet(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const void* const value, const bool overrideReadOnly);
void Ximu3SettingsSave(Ximu3Settings * const settings);

#endif

//------------------------------------------------------------------------------
// End of file
