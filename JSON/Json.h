/**
 * @file Json.h
 * @author Seb Madgwick
 * @brief Library for parsing of JSON strings.
 */

#ifndef JSON_H
#define JSON_H

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>
#include <stddef.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief JSON error.
 */
typedef enum {
    JsonErrorOK,
    JsonErrorInvalidSyntax,
    JsonErrorUnexpectedType,
    JsonErrorMissingObjectEnd,
    JsonErrorMissingArrayEnd,
    JsonErrorMissingComma,
    JsonErrorMissingKey,
    JsonErrorMissingColon,
    JsonErrorMissingStringEnd,
    JsonErrorStringTooLong,
    JsonErrorInvalidStringCharacter,
    JsonErrorInvalidStringEscapeSequence,
    JsonErrorInvalidStringHexEscapeSequence,
    JsonErrorUnableToParseStringHexEscapeSequence,
    JsonErrorInvalidNumberFormat,
    JsonErrorNumberTooLong,
    JsonErrorUnableToParseNumber,
} JsonError;

/**
 * @brief JSON types.
 */
typedef enum {
    JsonTypeString,
    JsonTypeNumber,
    JsonTypeObject,
    JsonTypeArray,
    JsonTypeBoolean,
    JsonTypeNull,
} JsonType;

//------------------------------------------------------------------------------
// Function declarations

JsonError JsonParseType(const char **const json, JsonType *const type);

JsonError JsonParseObjectStart(const char **const json);

JsonError JsonParseObjectEnd(const char **const json);

JsonError JsonParseArrayStart(const char **const json);

JsonError JsonParseArrayEnd(const char **const json);

JsonError JsonParseComma(const char **const json);

JsonError JsonParseKey(const char **const json, char *const destination, const size_t destinationSize);

JsonError JsonParseString(const char **const json, char *const destination, const size_t destinationSize, size_t *const numberOfBytes);

JsonError JsonParseNumber(const char **const json, float *const number);

JsonError JsonParseBoolean(const char **const json, bool *const boolean);

JsonError JsonParseNull(const char **const json);

JsonError JsonParse(const char **const json);

void JsonPrint(const char *json);

const char *JsonErrorToString(const JsonError error);

#ifdef __cplusplus
}
#endif

#endif

//------------------------------------------------------------------------------
// End of file
