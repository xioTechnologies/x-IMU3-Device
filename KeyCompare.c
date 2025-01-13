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
// Functions

/**
 * @brief Returns true if the keys match.  The comparison is not case sensitive
 * and non-alphanumeric characters will be ignored.
 * @param keyA Key A.
 * @param keyA Key B.
 */
bool KeyCompare(const char* const keyA, const char* const keyB) {
    size_t keyAIndex = 0;
    size_t keyBIndex = 0;

    while (true) {

        // Skip non-alphanumeric characters
        while ((isalnum(keyA[keyAIndex]) == 0) && (keyA[keyAIndex] != '\0')) {
            keyAIndex++;
        }
        while ((isalnum(keyB[keyBIndex]) == 0) && (keyB[keyBIndex] != '\0')) {
            keyBIndex++;
        }

        // Convert to lower case
        const char characterA = (isalpha(keyA[keyAIndex]) != 0) ? (char) tolower(keyA[keyAIndex]) : keyA[keyAIndex];
        const char characterB = (isalpha(keyB[keyBIndex]) != 0) ? (char) tolower(keyB[keyBIndex]) : keyB[keyBIndex];

        // Match failed if characters different
        if (characterA != characterB) {
            return false;
        }

        // Match if reached end of both strings
        if ((characterA == '\0') && (characterB == '\0')) {
            return true;
        }

        // Increment indexes
        keyAIndex++;
        keyBIndex++;
    }
}

//------------------------------------------------------------------------------
// End of file
