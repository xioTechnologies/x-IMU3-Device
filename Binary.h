/**
 * @file Binary.h
 * @author Seb Madgwick
 * @brief Binary data messages.
 */

#ifndef BINARY_H
#define BINARY_H

//------------------------------------------------------------------------------
// Includes

#include <stddef.h>
#include <stdint.h>
#include <string.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Byte stuffing end byte.
 */
#define BYTE_STUFFING_END 0x0A

/**
 * @brief Byte stuffing escape byte.
 */
#define BYTE_STUFFING_ESC 0xDB

/**
 * @brief Byte stuffing transposed end byte.
 */
#define BYTE_STUFFING_ESC_END 0xDC

/**
 * @brief Byte stuffing transposed escape byte.
 */
#define BYTE_STUFFING_ESC_ESC 0xDD

//------------------------------------------------------------------------------
// Inline functions

/**
 * @brief Writes a byte with byte stuffing.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param byte Byte.
 */
static inline void BinaryWrite(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const uint8_t byte) {
    if (*destinationIndex >= destinationSize) {
        return;
    }
    switch (byte) {
        case BYTE_STUFFING_END:
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC;
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC_END;
            break;
        case BYTE_STUFFING_ESC:
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC;
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC_ESC;
            break;
        default:
            ((uint8_t*) destination)[(*destinationIndex)++] = byte;
            break;
    }
}

/**
 * @brief Writes the first byte.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param character First character of equivalent ASCII data message.
 */
static inline void BinaryFirstByte(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char character) {
    BinaryWrite(destination, destinationSize, destinationIndex, 0x80 + character);
}

/**
 * @brief Writes the timestamp.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param timestamp Timestamp.
 */
static inline void BinaryTimestamp(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const uint64_t timestamp) {
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 0) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 8) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 16) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 24) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 32) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 40) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 48) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (timestamp >> 56) & 0xFF);
}

/**
 * @brief Writes a float.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param value Value.
 */
static inline void BinaryFloat(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const float value_) {
    uint32_t value;
    memcpy(&value, &value_, sizeof (value));
    BinaryWrite(destination, destinationSize, destinationIndex, (value >> 0) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (value >> 8) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (value >> 16) & 0xFF);
    BinaryWrite(destination, destinationSize, destinationIndex, (value >> 24) & 0xFF);
}

/**
 * @brief Writes a string.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param string String.
 */
static inline void BinaryString(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char* string) {
    while (*string != '\0') {
        BinaryWrite(destination, destinationSize, destinationIndex, *string++);
    }
}

/**
 * @brief Writes the termination.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 */
static inline void BinaryTermination(void* const destination, const size_t destinationSize, size_t * const destinationIndex) {
    if (*destinationIndex >= destinationSize) {
        return;
    }
    ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_END;
}

#endif

//------------------------------------------------------------------------------
// End of file
