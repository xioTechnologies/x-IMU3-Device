/**
 * @file Ximu3Command.h
 * @author Seb Madgwick
 * @brief x-IMU3 commands.
 */

#ifndef XIMU3_COMMAND_H
#define XIMU3_COMMAND_H

//------------------------------------------------------------------------------
// Includes

#include <stddef.h>
#include "Ximu3Definitions.h"
#include "Ximu3Settings.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Interface.
 */
typedef struct {
    const char* const name;
    size_t(*read)(void* const destination, size_t numberOfBytes);
    void(*write)(const void* const data, const size_t numberOfBytes);
    char buffer[XIMU3_OBJECT_SIZE];
    size_t index;
} Ximu3CommandInterface;

/**
 * @brief Response.
 */
typedef struct {
    const Ximu3CommandInterface* interface;
    char key[XIMU3_KEY_SIZE];
    char value[XIMU3_VALUE_SIZE];
} Ximu3CommandResponse;

/**
 * @brief Map.
 */
typedef struct {
    const char* const key;
    void (*callback)(const char* * const value, Ximu3CommandResponse * const response);
} Ximu3CommandMap;

/**
 * @brief Bridge.
 */
typedef struct {
    Ximu3CommandInterface * const interfaces;
    const int numberOfInterfaces;
    const Ximu3CommandMap * const commands;
    const int numberOfCommands;
    Ximu3Settings * const settings; // NULL if unused
    bool(*overrideReadOnly)(void); // NULL if unused
    void(*writeEpilogue)(const Ximu3SettingsIndex index); // NULL if unused
    void(*unknown)(const char* const key, const char* * const value, Ximu3CommandResponse * const response); // NULL if unused
    void(*error)(const char* const error); // NULL if unused
} Ximu3CommandBridge;

//------------------------------------------------------------------------------
// Function declarations

void Ximu3CommandTasks(Ximu3CommandBridge * const bridge);
int Ximu3CommandParseString(const char* * const value, Ximu3CommandResponse * const response, char* const destination, const size_t destinationSize, size_t * const numberOfBytes);
int Ximu3CommandParseNumber(const char* * const value, Ximu3CommandResponse * const response, float *const number);
int Ximu3CommandParseBoolean(const char* * const value, Ximu3CommandResponse * const response, bool *const boolean);
int Ximu3CommandParseNull(const char* * const value, Ximu3CommandResponse * const response);
void Ximu3CommandRespond(Ximu3CommandResponse * const response);
void Ximu3CommandRespondPing(Ximu3CommandResponse * const response, const char* const name, const char* const sn);
void Ximu3CommandRespondError(Ximu3CommandResponse * const response, const char* const error);

#endif

//------------------------------------------------------------------------------
// End of file