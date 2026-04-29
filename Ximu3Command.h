/**
 * @file Ximu3Command.h
 * @author Seb Madgwick
 * @brief x-IMU3 commands.
 */

#ifndef XIMU3_COMMAND_H
#define XIMU3_COMMAND_H

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Ximu3Definitions.h"
#include "Ximu3Settings.h"
#include "Ximu3Size.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Interface.
 */
typedef struct {
    const char* const name;
    size_t(*const read)(void* const destination, size_t numberOfBytes, void* const context);
    void (*const write) (const void* const data, const size_t numberOfBytes, void* const context);
    uint8_t buffer[XIMU3_SIZE_COMMAND]; // private
    size_t index; // private
} Ximu3CommandInterface;

/**
 * @brief Response.
 */
typedef struct {
    const Ximu3CommandInterface* interface;
    char key[XIMU3_SIZE_KEY];
    char value[XIMU3_SIZE_VALUE];
    void* context;
} Ximu3CommandResponse;

/**
 * @brief Map.
 */
typedef struct {
    const char* const key;
    void (*const callback) (const char* * const value, Ximu3CommandResponse * const response, void* const context);
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
    bool (*const overrideReadOnly) (void* const context); // NULL if unused
    void (*const writeEpilogue) (const Ximu3SettingsIndex index, const void* const value, void* const context); // NULL if unused
    void (*const unknown) (const char* const key, const char* * const value, Ximu3CommandResponse * const response, void* const context); // NULL if unused
    Ximu3Result(*const mux)(const Ximu3CommandInterface * const interface, const uint8_t channel, const void* const message, const size_t messageSize); // NULL if unused
    void (*const error) (const char* const error, void* const context); // NULL if unused
    void* context;
} Ximu3CommandBridge;

//------------------------------------------------------------------------------
// Function declarations

void Ximu3CommandTasks(Ximu3CommandBridge * const bridge);
void Ximu3CommandReceive(const Ximu3CommandBridge * const bridge, const Ximu3CommandInterface * const interface, const void* const data, const size_t numberOfBytes);
void Ximu3CommandExecute(const Ximu3CommandBridge * const bridge, const Ximu3CommandInterface * const interface, const char* const key, const char* const value);
Ximu3Result Ximu3CommandParseString(const char* * const value, Ximu3CommandResponse * const response, char* const destination, const size_t destinationSize, size_t * const numberOfBytes);
Ximu3Result Ximu3CommandParseNumber(const char* * const value, Ximu3CommandResponse * const response, float* const number);
Ximu3Result Ximu3CommandParseNumberU64(const char* * const value, Ximu3CommandResponse * const response, uint64_t * const number);
Ximu3Result Ximu3CommandParseBoolean(const char* * const value, Ximu3CommandResponse * const response, bool * const boolean);
Ximu3Result Ximu3CommandParseNull(const char* * const value, Ximu3CommandResponse * const response);
void Ximu3CommandRespond(Ximu3CommandResponse * const response);
void Ximu3CommandRespondPing(Ximu3CommandResponse * const response, const char* const deviceName, const char* const serialNumber);
void Ximu3CommandRespondError(Ximu3CommandResponse * const response, const char* const error);

#endif

//------------------------------------------------------------------------------
// End of file
