/**
 * @file Json.c
 * @author Seb Madgwick
 * @brief Library for parsing of JSON strings.
 */

//------------------------------------------------------------------------------
// Includes

#include <ctype.h>
#include "Json.h"
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
// Function declarations

static void SkipWhiteSpace(const char **const json);

static JsonError CheckType(const char **const json, const JsonType expectedType);

static JsonError ParseEscapeSequence(const char **const json, char *const destination, size_t *const index);

static JsonError ParseHexEscapeSequence(const char **const json, char *const destination, size_t *const index);

static void WriteToDestination(char *const destination, size_t *const index, const char character);

static JsonError ParseValue(const char **const json, const bool print, int *const indent);

static JsonError ParseObject(const char **const json, const bool print, int *const indent);

static JsonError ParseArray(const char **const json, const bool print, int *const indent);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Parses value type.  The JSON pointer is not modified.
 * @param json JSON pointer.
 * @param type Type.
 * @return JSON error.
 */
JsonError JsonParseType(const char **const json, JsonType *const type) {
    SkipWhiteSpace(json);
    switch (**json) {
        case '"':
            *type = JsonTypeString;
            return JsonErrorOK;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            *type = JsonTypeNumber;
            return JsonErrorOK;
        case '{':
            *type = JsonTypeObject;
            return JsonErrorOK;
        case '[':
            *type = JsonTypeArray;
            return JsonErrorOK;
        case 't':
        case 'f':
            *type = JsonTypeBoolean;
            return JsonErrorOK;
        case 'n':
            *type = JsonTypeNull;
            return JsonErrorOK;
        default:
            return JsonErrorInvalidSyntax;
    }
}

/**
 * @brief Advances the JSON pointer to the first non-whitespace character.
 * @param json JSON pointer.
 */
static void SkipWhiteSpace(const char **const json) {
    while (true) {
        switch (**json) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                (*json)++;
                break;
            default:
                return;
        }
    }
}

/**
 * @brief Checks that the type matches the expected type.  The JSON pointer is
 * not modified.
 * @param json JSON pointer.
 * @param expectedType Expected type.
 * @return JSON error.
 */
static JsonError CheckType(const char **const json, const JsonType expectedType) {
    JsonType type;
    const JsonError error = JsonParseType(json, &type);
    if (error != JsonErrorOK) {
        return error;
    }
    if (type != expectedType) {
        return JsonErrorUnexpectedType;
    }
    return JsonErrorOK;
}

/**
 * @brief Parses an object start.  The JSON pointer is advanced to the first
 * non-whitespace character after the object start.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParseObjectStart(const char **const json) {
    const JsonError error = CheckType(json, JsonTypeObject);
    if (error != JsonErrorOK) {
        return error;
    }
    (*json)++;
    SkipWhiteSpace(json);
    return JsonErrorOK;
}

/**
 * @brief Parses an object end.  The JSON pointer is advanced to the first
 * character after the object end.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParseObjectEnd(const char **const json) {
    SkipWhiteSpace(json);
    if (**json != '}') {
        return JsonErrorMissingObjectEnd;
    }
    (*json)++;
    return JsonErrorOK;
}

/**
 * @brief Parses an array start.  The JSON pointer is advanced to the first
 * non-whitespace character after the object start.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParseArrayStart(const char **const json) {
    const JsonError error = CheckType(json, JsonTypeArray);
    if (error != JsonErrorOK) {
        return error;
    }
    (*json)++;
    SkipWhiteSpace(json);
    return JsonErrorOK;
}

/**
 * @brief Parses an array end.  The JSON pointer is advanced to the first
 * character after the array end.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParseArrayEnd(const char **const json) {
    SkipWhiteSpace(json);
    if (**json != ']') {
        return JsonErrorMissingArrayEnd;
    }
    (*json)++;
    return JsonErrorOK;
}

/**
 * @brief Parses a comma.  The JSON pointer is advanced to the first character
 * after the comma.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParseComma(const char **const json) {
    SkipWhiteSpace(json);
    if (**json != ',') {
        return JsonErrorMissingComma;
    }
    (*json)++;
    return JsonErrorOK;
}

/**
 * @brief Parses the key in a JSON object.  The JSON pointer is advanced to the
 * character after the colon that separates the key/value pair.
 * @param json JSON pointer.
 * @param destination Destination.  NULL if not required.
 * @param destinationSize Destination size.
 * @return JSON error.
 */
JsonError JsonParseKey(const char **const json, char *const destination, const size_t destinationSize) {
    // Check type
    if (CheckType(json, JsonTypeString) != JsonErrorOK) {
        return JsonErrorMissingKey;
    }

    // Parse key
    const JsonError error = JsonParseString(json, destination, destinationSize, NULL);
    if (error != JsonErrorOK) {
        return error;
    }

    // Parse colon
    SkipWhiteSpace(json);
    if (**json != ':') {
        return JsonErrorMissingColon;
    }
    (*json)++;
    return JsonErrorOK;
}

/**
 * @brief Parse string.  The JSON pointer is advanced to the first
 * character after the string.
 * @param json JSON pointer.
 * @param destination Destination.  NULL if not required.
 * @param destinationSize Destination size.
 * @param numberOfBytes Number of bytes in string.  NULL if not required.
 * @return JSON error.
 */
JsonError JsonParseString(const char **const json, char *const destination, const size_t destinationSize, size_t *const numberOfBytes) {
    // Check type
    JsonError error = CheckType(json, JsonTypeString);
    if (error != JsonErrorOK) {
        return error;
    }
    (*json)++;

    // Parse string
    size_t index = 0;
    while (true) {
        if ((destination != NULL) && (index >= destinationSize)) {
            return JsonErrorStringTooLong;
        }
        if (**json == '\0') {
            return JsonErrorMissingStringEnd;
        }
        if ((**json >= 0) && (**json < 0x20)) {
            return JsonErrorInvalidStringCharacter; // control charcaters must be escaped
        }
        if (**json == '\\') {
            error = ParseEscapeSequence(json, destination, &index);
            if (error != JsonErrorOK) {
                return error;
            }
            continue;
        }
        if (**json == '\"') {
            (*json)++;
            WriteToDestination(destination, &index, '\0');
            if (numberOfBytes != NULL) {
                *numberOfBytes = index;
            }
            return JsonErrorOK;
        }
        WriteToDestination(destination, &index, *(*json)++);
    }
}

/**
 * @brief Parse escape sequence.  The JSON pointer is advanced to the first
 * character after the escape sequence.
 * @param json JSON pointer.
 * @param destination Destination.
 * @param index Index.
 * @return JSON error.
 */
static JsonError ParseEscapeSequence(const char **const json, char *const destination, size_t *const index) {
    switch (*(*json + 1)) {
        case '\"':
            WriteToDestination(destination, index, '"');
            break;
        case '\\':
            WriteToDestination(destination, index, '\\');
            break;
        case '/':
            WriteToDestination(destination, index, '/');
            break;
        case 'b':
            WriteToDestination(destination, index, '\b');
            break;
        case 'f':
            WriteToDestination(destination, index, '\f');
            break;
        case 'n':
            WriteToDestination(destination, index, '\n');
            break;
        case 'r':
            WriteToDestination(destination, index, '\r');
            break;
        case 't':
            WriteToDestination(destination, index, '\t');
            break;
        case 'u':
            return ParseHexEscapeSequence(json, destination, index);
        default:
            return JsonErrorInvalidStringEscapeSequence;
    }
    (*json) += 2;
    return JsonErrorOK;
}

/**
 * @brief Parse hex escape sequence.  The JSON pointer is advanced to the
 * first character after the hex escape sequence.
 * @param json JSON pointer.
 * @param destination Destination.
 * @param index Index.
 * @return JSON error.
 */
static JsonError ParseHexEscapeSequence(const char **const json, char *const destination, size_t *const index) {
    if (isxdigit((int) *(*json + 2)) == 0) {
        return JsonErrorInvalidStringHexEscapeSequence;
    }
    if (isxdigit((int) *(*json + 3)) == 0) {
        return JsonErrorInvalidStringHexEscapeSequence;
    }
    if (isxdigit((int) *(*json + 4)) == 0) {
        return JsonErrorInvalidStringHexEscapeSequence;
    }
    if (isxdigit((int) *(*json + 5)) == 0) {
        return JsonErrorInvalidStringHexEscapeSequence;
    }
    char string[5];
    snprintf(string, sizeof(string), "%s", *json + 2);
    unsigned int value;
    if (sscanf(string, "%x", &value) != 1) {
        return JsonErrorUnableToParseStringHexEscapeSequence;
    }
    WriteToDestination(destination, index, (char) value);
    (*json) += 6;
    return JsonErrorOK;
}

/**
 * @brief Writes character to destination and increments index, if destination is
 * not NULL.
 * @param destination Destination.
 * @param index Index.
 * @param character Character.
 */
static void WriteToDestination(char *const destination, size_t *const index, const char character) {
    if (destination != NULL) {
        destination[(*index)++] = character;
    }
}

/**
 * @brief Parses number.  The JSON pointer is advanced to the first character
 * after the number.
 * @param json JSON pointer.
 * @param number Number.  NULL if not required.
 * @return JSON error.
 */
JsonError JsonParseNumber(const char **const json, float *const number) {
    // Check type
    const JsonError error = CheckType(json, JsonTypeNumber);
    if (error != JsonErrorOK) {
        return error;
    }

    // Parse sign
    const char *jsonCopy = *json;
    if (*jsonCopy == '-') {
        jsonCopy++;
        if (isdigit((int) *jsonCopy) == 0) {
            return JsonErrorInvalidNumberFormat; // minus sign must be followed by digit
        }
    }

    // Parse first zero
    if (*jsonCopy == '0') {
        jsonCopy++;
        if (*jsonCopy == '0') {
            return JsonErrorInvalidNumberFormat; // leading zeros are invalid
        }
    }

    // Parse integer
    while (isdigit((int) *jsonCopy) != 0) {
        jsonCopy++;
    }

    // Parse fraction
    if (*jsonCopy == '.') {
        jsonCopy++;
        if (isdigit((int) *jsonCopy) == 0) {
            return JsonErrorInvalidNumberFormat; // decimal point must be followed by digit
        }
    }
    while (isdigit((int) *jsonCopy) != 0) {
        jsonCopy++;
    }

    // Parse exponent
    if ((*jsonCopy == 'e') || (*jsonCopy == 'E')) {
        jsonCopy++;
        if ((*jsonCopy == '+') || (*jsonCopy == '-')) {
            jsonCopy++;
        }
        if (isdigit((int) *jsonCopy) == 0) {
            return JsonErrorInvalidNumberFormat; // exponent must be followed by digit
        }
    }
    while (isdigit((int) *jsonCopy) != 0) {
        jsonCopy++;
    }

    // Read number string
    if (number != NULL) {
        char string[32];
        const size_t numberOfBytes = jsonCopy - *json;
        if (numberOfBytes >= sizeof(string)) {
            return JsonErrorNumberTooLong;
        }
        snprintf(string, sizeof(string), "%s", *json);
        if (sscanf(string, "%f", number) != 1) {
            return JsonErrorUnableToParseNumber;
        }
    }
    *json = jsonCopy;
    return JsonErrorOK;
}

/**
 * @brief Parses boolean.  The JSON pointer is advanced to the first character
 * after the boolean.
 * @param json JSON pointer.
 * @param boolean Boolean.  NULL if not required.
 * @return JSON error.
 */
JsonError JsonParseBoolean(const char **const json, bool *const boolean) {
    // Check type
    const JsonError error = CheckType(json, JsonTypeBoolean);
    if (error != JsonErrorOK) {
        return error;
    }

    // Parse true
    const char trueString[] = "true";
    if (strncmp(*json, trueString, sizeof(trueString) - 1) == 0) {
        (*json) += sizeof(trueString) - 1;
        if (boolean != NULL) {
            *boolean = true;
        }
        return JsonErrorOK;
    }

    // Parse false
    const char falseString[] = "false";
    if (strncmp(*json, falseString, sizeof(falseString) - 1) == 0) {
        (*json) += sizeof(falseString) - 1;
        if (boolean != NULL) {
            *boolean = false;
        }
        return JsonErrorOK;
    }
    return JsonErrorInvalidSyntax;
}

/**
 * @brief Parses null.  The JSON pointer is advanced to the first character
 * after the null.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParseNull(const char **const json) {
    // Check type
    const JsonError error = CheckType(json, JsonTypeNull);
    if (error != JsonErrorOK) {
        return error;
    }

    // Parse null
    const char nullString[] = "null";
    if (strncmp(*json, nullString, sizeof(nullString) - 1) == 0) {
        (*json) += sizeof(nullString) - 1;
        return JsonErrorOK;
    }
    return JsonErrorInvalidSyntax;
}

/**
 * @brief Parses any JSON and discards data.  The JSON pointer is advanced to
 * the first character after the JSON.
 * @param json JSON pointer.
 * @return JSON error.
 */
JsonError JsonParse(const char **const json) {
    int indent = 0;
    return ParseValue(json, false, &indent);
}

/**
 * @brief Prints the JSON structure and error message.
 * @param json_ JSON pointer.
 */
void JsonPrint(const char *json_) {
    int indent = 0;
    const char **const json = &json_;
    const JsonError error = ParseValue(json, true, &indent);
    printf("%s\n", JsonErrorToString(error));
}

/**
 * @brief Parses value and discards data.  The JSON pointer is advanced to the
 * first character after the value.
 * @param json JSON pointer.
 * @param print True to print.
 * @param indent Indent.
 * @return JSON error.
 */
static JsonError ParseValue(const char **const json, const bool print, int *const indent) {
    // Parse value type
    JsonType type;
    const JsonError error = JsonParseType(json, &type);
    if (error != JsonErrorOK) {
        return error;
    }

    // Print value type
    if (print) {
        const int actualIndent = 4 * *indent;
        switch (type) {
            case JsonTypeString:
                printf("%*sstring\n", actualIndent, "");
                break;
            case JsonTypeNumber:
                printf("%*snumber\n", actualIndent, "");
                break;
            case JsonTypeObject:
                printf("%*sobject\n", actualIndent, "");
                break;
            case JsonTypeArray:
                printf("%*sarray\n", actualIndent, "");
                break;
            case JsonTypeBoolean:
                printf("%*sboolean\n", actualIndent, "");
                break;
            case JsonTypeNull:
                printf("%*snull\n", actualIndent, "");
                break;
        }
    }

    // Parse value
    switch (type) {
        case JsonTypeString:
            return JsonParseString(json, NULL, 0, NULL);
        case JsonTypeNumber:
            return JsonParseNumber(json, NULL);
        case JsonTypeObject:
            return ParseObject(json, print, indent);
        case JsonTypeArray:
            return ParseArray(json, print, indent);
        case JsonTypeBoolean:
            return JsonParseBoolean(json, NULL);
        case JsonTypeNull:
            return JsonParseNull(json);
    }
    return JsonErrorOK;
}

/**
 * @brief Parses object and discards data.  The JSON pointer is advanced to the
 * first character after the object.
 * @param json JSON pointer.
 * @param print True to print.
 * @param indent Indent.
 * @return JSON error.
 */
static JsonError ParseObject(const char **const json, const bool print, int *const indent) {
    // Parse object start
    JsonError error = JsonParseObjectStart(json);
    if (error != JsonErrorOK) {
        return error;
    }

    // Parse object end
    error = JsonParseObjectEnd(json);
    if (error == JsonErrorOK) {
        return JsonErrorOK;
    }

    // Loop through each key/value pair
    (*indent)++;
    while (true) {
        // Parse key
        char key[64];
        error = JsonParseKey(json, key, sizeof(key));
        if (error != JsonErrorOK) {
            return error;
        }

        // Parse value
        error = ParseValue(json, print, indent);
        if (error != JsonErrorOK) {
            return error;
        }

        // Parse comma
        error = JsonParseComma(json);
        if (error == JsonErrorOK) {
            continue;
        }

        // Parse object end
        error = JsonParseObjectEnd(json);
        if (error != JsonErrorOK) {
            return error;
        }
        break;
    }
    (*indent)--;
    return JsonErrorOK;
}

/**
 * @brief Parses array and discards data.  The JSON pointer is advanced to the
 * first character after the array.
 * @param json JSON pointer.
 * @param print True to print.
 * @param indent Indent.
 * @return JSON error.
 */
static JsonError ParseArray(const char **const json, const bool print, int *const indent) {
    // Parse array start
    JsonError error = JsonParseArrayStart(json);
    if (error != JsonErrorOK) {
        return error;
    }

    // Parse array end
    error = JsonParseArrayEnd(json);
    if (error == JsonErrorOK) {
        return JsonErrorOK;
    }

    // Loop through each value
    (*indent)++;
    while (true) {
        // Parse value
        error = ParseValue(json, print, indent);
        if (error != JsonErrorOK) {
            return error;
        }

        // Parse comma
        error = JsonParseComma(json);
        if (error == JsonErrorOK) {
            continue;
        }

        // Parse array end
        error = JsonParseArrayEnd(json);
        if (error != JsonErrorOK) {
            return error;
        }
        break;
    }
    (*indent)--;
    return JsonErrorOK;
}

/**
 * @brief Returns the JSON error message.
 * @param error JSON error.
 * @return JSON error message.
 */
const char *JsonErrorToString(const JsonError error) {
    switch (error) {
        case JsonErrorOK:
            return "OK";
        case JsonErrorInvalidSyntax:
            return "Invalid syntax";
        case JsonErrorUnexpectedType:
            return "Unexpected type";
        case JsonErrorMissingObjectEnd:
            return "Missing object end";
        case JsonErrorMissingArrayEnd:
            return "Missing array end";
        case JsonErrorMissingComma:
            return "Missing comma";
        case JsonErrorMissingKey:
            return "Missing key";
        case JsonErrorMissingColon:
            return "Missing colon";
        case JsonErrorMissingStringEnd:
            return "Missing string end";
        case JsonErrorStringTooLong:
            return "String too long";
        case JsonErrorInvalidStringCharacter:
            return "Invalid string character";
        case JsonErrorInvalidStringEscapeSequence:
            return "Invalid string escape sequence";
        case JsonErrorInvalidStringHexEscapeSequence:
            return "Invalid string hex escape sequence";
        case JsonErrorUnableToParseStringHexEscapeSequence:
            return "Unable to parse string hex escape sequence";
        case JsonErrorInvalidNumberFormat:
            return "Invalid number format";
        case JsonErrorNumberTooLong:
            return "Number too long";
        case JsonErrorUnableToParseNumber:
            return "Unable to parse number";
    }
    return ""; // avoid compiler warning
}

//------------------------------------------------------------------------------
// End of file
