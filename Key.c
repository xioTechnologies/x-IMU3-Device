/**
 * @file Key.c
 * @author Seb Madgwick
 * @brief JSON key comparison.
 */

//------------------------------------------------------------------------------
// Includes

#include <ctype.h>
#include "Key.h"
#include <stddef.h>

//------------------------------------------------------------------------------
// Function declarations

static inline void SkipNonAlphanumeric(const char* * const string);
static inline char ToLower(const char character);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Returns true if key A matches key B. The comparison is not case-
 * sensitive and non-alphanumeric characters will be ignored for the purposes of
 * comparison.
 * @param a Key A.
 * @param b Key B.
 * @return True if key A matches key B.
 */
bool KeyMatches(const char* a, const char* b) {
    while (true) {
        SkipNonAlphanumeric(&a);
        SkipNonAlphanumeric(&b);
        if (ToLower(*a) != ToLower(*b)) {
            return false;
        }
        if ((*a == '\0') && (*b == '\0')) {
            return true;
        }
        a++;
        b++;
    }
}

/**
 * @brief Returns true if key A starts with key B. The comparison is not case-
 * sensitive and non-alphanumeric characters will be ignored for the purposes
 * of comparison. The key A pointer will be advanced to the first alphanumeric
 * character after the match.
 * @param a Key A.
 * @param b Key B.
 * @return True if key A starts with B.
 */
bool KeyStartsWith(const char* * const a, const char* b) {
    while (true) {
        SkipNonAlphanumeric(a);
        SkipNonAlphanumeric(&b);
        if (*b == '\0') {
            return true;
        }
        if (**a == '\0') {
            return false;
        }
        if (ToLower(**a) != ToLower(*b)) {
            return false;
        }
        (*a)++;
        b++;
    }
}

/**
 * @brief Advances the pointer to first alphanumeric character.
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
