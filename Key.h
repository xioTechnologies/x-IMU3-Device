/**
 * @file Key.h
 * @author Seb Madgwick
 * @brief JSON key comparison.
 */

#ifndef KEY_H
#define KEY_H

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>

//------------------------------------------------------------------------------
// Function declarations

bool KeyMatches(const char* a, const char* b);
bool KeyStartsWith(const char* * const a, const char* b);

#endif

//------------------------------------------------------------------------------
// End of file
