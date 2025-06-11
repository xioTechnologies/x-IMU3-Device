/**
 * @file Ximu3SettingsJson.h
 * @author Seb Madgwick
 * @brief x-IMU3 settings JSON.
 */

#ifndef XIMU3_SETTINGS_JSON_H
#define XIMU3_SETTINGS_JSON_H

//------------------------------------------------------------------------------
// Includes

#include "JSON/Json.h"
#include <stdbool.h>
#include <stddef.h>
#include "Ximu3Definitions.h"

//------------------------------------------------------------------------------
// Function declarations

Ximu3Result Ximu3SettingsJsonGetIndex(Ximu3Settings * const settings, Ximu3SettingsIndex * const index_, const char* const key);
void Ximu3SettingsJsonGetKey(Ximu3Settings * const settings, char* const destination, const size_t destinationSize, const Ximu3SettingsIndex index);
void Ximu3SettingsJsonGetValue(Ximu3Settings * const settings, char* const destination, const size_t destinationSize, const Ximu3SettingsIndex index);
void Ximu3SettingsJsonGetObject(Ximu3Settings * const settings, char* const destination, const size_t destinationSize, const Ximu3SettingsIndex index);
void Ximu3SettingsJsonGetObjectAll(Ximu3Settings * const settings, char* const destination, const size_t destinationSize);
JsonResult Ximu3SettingsJsonSetKeyValue(Ximu3Settings * const settings, const char* const key, const char* * const value, const bool overrideReadOnly);
JsonResult Ximu3SettingsJsonSetObject(Ximu3Settings * const settings, const char* object_, const bool overrideReadOnly);

#endif

//------------------------------------------------------------------------------
// End of file
