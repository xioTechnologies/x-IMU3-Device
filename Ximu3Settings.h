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
#include "Ximu3Definitions.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Settings.
 */
typedef struct {
    void (*const nvmRead) (void* const destination, size_t numberOfBytes, void* const context); // NULL if unused
    void (*const nvmWrite) (const void* const data, const size_t numberOfBytes, void* const context); // NULL if unused
    void (*const initialiseEpilogue) (void* const context); // NULL if unused
    void (*const defaultsEpilogue) (void* const context); // NULL if unused
    void* context;
    Ximu3SettingsValues values; // private
    bool applied[XIMU3_NUMBER_OF_SETTINGS]; // private
} Ximu3Settings;

//------------------------------------------------------------------------------
// Function declarations

void Ximu3SettingsInitialise(Ximu3Settings * const settings);
void Ximu3SettingsDefaults(Ximu3Settings * const settings, const bool overwritePreserved);
const Ximu3SettingsValues* Ximu3SettingsGet(const Ximu3Settings * const settings);
void Ximu3SettingsSet(Ximu3Settings * const settings, const Ximu3SettingsIndex index, const void* const value, const bool overrideReadOnly);
void Ximu3SettingsSave(const Ximu3Settings * const settings);
bool Ximu3SettingsApplyPending(Ximu3Settings * const settings, const Ximu3SettingsIndex index);

#endif

//------------------------------------------------------------------------------
// End of file
