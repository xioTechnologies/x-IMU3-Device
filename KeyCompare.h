/**
 * @file KeyCompare.h
 * @author Seb Madgwick
 * @brief Compares two JSON keys.
 */

#ifndef KEY_COMPARE_H
#define KEY_COMPARE_H

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>

//------------------------------------------------------------------------------
// Function declarations

bool KeyCompare(const char* input, const char* target);
bool KeyComparePartial(const char* * const input, const char* target);

#endif

//------------------------------------------------------------------------------
// End of file
