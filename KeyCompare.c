/**
 * @file KeyCompare.c
 * @author Seb Madgwick
 * @brief Compares two JSON keys.
 */

//------------------------------------------------------------------------------
// Includes

#include <ctype.h>
#include "KeyCompare.h"
#include <stddef.h>

//------------------------------------------------------------------------------
// Function declarations

static inline void SkipNonAlphanumeric(const char* * const string);
static inline char ToLower(const char character);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Returns true if the input key matches the target key. The comparison
 * is not case-sensitive and non-alphanumeric characters will be ignored.
 * @param input Input key.
 * @param target Target key.
 * @return True if the input key matches the target key.
 */
bool KeyCompare(const char* input, const char* target) {
    while (true) {
        SkipNonAlphanumeric(&input);
        SkipNonAlphanumeric(&target);
        if (ToLower(*input) != ToLower(*target)) {
            return false;
        }
        if ((*input == '\0') && (*target == '\0')) {
            return true;
        }
        input++;
        target++;
    }
}

/**
 * @brief Returns true if the input key start with the target key.  The
 * comparison is not case-sensitive and non-alphanumeric characters will be
 * ignored. The input key pointer will be advanced to the first alphanumeric
 * character after the match.
 * @param input Input key.
 * @param target Target key.
 * @return True if the input key start with the target key.
 */
bool KeyComparePartial(const char* * const input, const char* target) {
    while (true) {
        SkipNonAlphanumeric(input);
        SkipNonAlphanumeric(&target);
        if (*target == '\0') {
            return true;
        }
        if (**input == '\0') {
            return false;
        }
        if (ToLower(**input) != ToLower(*target)) {
            return false;
        }
        (*input)++;
        target++;
    }
}

/**
 * @brief Advances pointer to first alphanumeric character.
 * @param string String.
 */
static inline void SkipNonAlphanumeric(const char* * const string) {
    while ((**string != '\0') && (isalnum((unsigned char) **string) == 0)) {
        (*string)++;
    }
}

/**
 * @brief Returns the lower-case character.
 * @param character Character.
 */
static inline char ToLower(const char character) {
    if (isalpha((unsigned char) character) == 0) {
        return character;
    }
    return (char) tolower((unsigned char) character);
}

//------------------------------------------------------------------------------
// End of file
