/**
 * @file Ximu3Binary.c
 * @author Seb Madgwick
 * @brief x-IMU3 binary data messages.
 */

//------------------------------------------------------------------------------
// Includes

#include <string.h>
#include "Ximu3Ascii.h"
#include "Ximu3Binary.h"
#include "Ximu3Definitions.h"

//------------------------------------------------------------------------------
// Definitions

#define BYTE_STUFFING_END       XIMU3_TERMINATION
#define BYTE_STUFFING_ESC       (0xDB)
#define BYTE_STUFFING_ESC_END   (0xDC)
#define BYTE_STUFFING_ESC_ESC   (0xDD)

//------------------------------------------------------------------------------
// Function declarations

static inline void WriteHeader(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char asciiId, const uint64_t timestamp);
static inline void WriteFloat(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const float value_);
static inline void WriteString(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char* string);
static inline void WriteTermination(void* const destination, const size_t destinationSize, size_t * const destinationIndex);
static inline void WriteByte(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const uint8_t byte);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Writes a binary inertial data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryInertial(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_INERTIAL, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->gyroscopeX);
    WriteFloat(destination, destinationSize, &destinationIndex, data->gyroscopeY);
    WriteFloat(destination, destinationSize, &destinationIndex, data->gyroscopeZ);
    WriteFloat(destination, destinationSize, &destinationIndex, data->accelerometerX);
    WriteFloat(destination, destinationSize, &destinationIndex, data->accelerometerY);
    WriteFloat(destination, destinationSize, &destinationIndex, data->accelerometerZ);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary magnetometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryMagnetometer(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_MAGNETOMETER, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->x);
    WriteFloat(destination, destinationSize, &destinationIndex, data->y);
    WriteFloat(destination, destinationSize, &destinationIndex, data->z);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary high-g accelerometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryHighGAccelerometer(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_HIGH_G_ACCELEROMETER, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->x);
    WriteFloat(destination, destinationSize, &destinationIndex, data->y);
    WriteFloat(destination, destinationSize, &destinationIndex, data->z);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary quaternion data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryQuaternion(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_QUATERNION, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->w);
    WriteFloat(destination, destinationSize, &destinationIndex, data->x);
    WriteFloat(destination, destinationSize, &destinationIndex, data->y);
    WriteFloat(destination, destinationSize, &destinationIndex, data->z);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary rotation matrix data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryRotationMatrix(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_ROTATION_MATRIX, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->xx);
    WriteFloat(destination, destinationSize, &destinationIndex, data->xy);
    WriteFloat(destination, destinationSize, &destinationIndex, data->xz);
    WriteFloat(destination, destinationSize, &destinationIndex, data->yx);
    WriteFloat(destination, destinationSize, &destinationIndex, data->yy);
    WriteFloat(destination, destinationSize, &destinationIndex, data->yz);
    WriteFloat(destination, destinationSize, &destinationIndex, data->zx);
    WriteFloat(destination, destinationSize, &destinationIndex, data->zy);
    WriteFloat(destination, destinationSize, &destinationIndex, data->zz);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary Euler angles data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryEulerAngles(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_EULER_ANGLES, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->roll);
    WriteFloat(destination, destinationSize, &destinationIndex, data->pitch);
    WriteFloat(destination, destinationSize, &destinationIndex, data->yaw);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary linear acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryLinearAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_LINEAR_ACCELERATION, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionW);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionX);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionY);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionZ);
    WriteFloat(destination, destinationSize, &destinationIndex, data->linearAccelerationX);
    WriteFloat(destination, destinationSize, &destinationIndex, data->linearAccelerationY);
    WriteFloat(destination, destinationSize, &destinationIndex, data->linearAccelerationZ);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary Earth acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryEarthAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_EARTH_ACCELERATION, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionW);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionX);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionY);
    WriteFloat(destination, destinationSize, &destinationIndex, data->quaternionZ);
    WriteFloat(destination, destinationSize, &destinationIndex, data->earthAccelerationX);
    WriteFloat(destination, destinationSize, &destinationIndex, data->earthAccelerationY);
    WriteFloat(destination, destinationSize, &destinationIndex, data->earthAccelerationZ);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary AHRS status data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryAhrsStatus(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_AHRS_STATUS, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, (float) data->initialising);
    WriteFloat(destination, destinationSize, &destinationIndex, (float) data->angularRateRecovery);
    WriteFloat(destination, destinationSize, &destinationIndex, (float) data->accelerationRecovery);
    WriteFloat(destination, destinationSize, &destinationIndex, (float) data->magneticRecovery);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary serial accessory data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinarySerialAccessory(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_SERIAL_ACCESSORY, data->timestamp);
    for (size_t index = 0; index < data->numberOfBytes; index++) {
        WriteByte(destination, destinationSize, &destinationIndex, data->data[index]);
    }
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary sync data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinarySync(void* const destination, const size_t destinationSize, const Ximu3DataSync * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_SYNC, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, (float) data->edge);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary LTC data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryLtc(void* const destination, const size_t destinationSize, const Ximu3DataLtc * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_LTC, data->timestamp);
    WriteString(destination, destinationSize, &destinationIndex, data->timecode);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary temperature data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryTemperature(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_TEMPERATURE, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->temperature);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary battery data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryBattery(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_BATTERY, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->percentage);
    WriteFloat(destination, destinationSize, &destinationIndex, data->voltage);
    WriteFloat(destination, destinationSize, &destinationIndex, data->chargingStatus);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary RSSI data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryRssi(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_RSSI, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->percentage);
    WriteFloat(destination, destinationSize, &destinationIndex, data->power);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary button data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryButton(void* const destination, const size_t destinationSize, const Ximu3DataButton * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_BUTTON, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, (float) data->state);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary notification data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryNotification(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_NOTIFICATION, data->timestamp);
    WriteString(destination, destinationSize, &destinationIndex, data->notification);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes a binary error data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3BinaryError(void* const destination, const size_t destinationSize, const Ximu3DataError * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_ERROR, data->timestamp);
    WriteString(destination, destinationSize, &destinationIndex, data->error);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes the header.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param asciiId ASCII data message ID.
 * @param timestamp Timestamp.
 */
static inline void WriteHeader(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char asciiId, const uint64_t timestamp) {
    WriteByte(destination, destinationSize, destinationIndex, 0x80 + (uint8_t) asciiId);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 0) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 8) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 16) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 24) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 32) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 40) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 48) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (timestamp >> 56) & 0xFF);
}

/**
 * @brief Writes a float.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param value Value.
 */
static inline void WriteFloat(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const float value_) {
    uint32_t value;
    memcpy(&value, &value_, sizeof (value));
    WriteByte(destination, destinationSize, destinationIndex, (value >> 0) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (value >> 8) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (value >> 16) & 0xFF);
    WriteByte(destination, destinationSize, destinationIndex, (value >> 24) & 0xFF);
}

/**
 * @brief Writes a string.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param string String.
 */
static inline void WriteString(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char* string) {
    while (*string != '\0') {
        WriteByte(destination, destinationSize, destinationIndex, (uint8_t) * string++);
    }
}

/**
 * @brief Writes the termination.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 */
static inline void WriteTermination(void* const destination, const size_t destinationSize, size_t * const destinationIndex) {
    if (*destinationIndex >= destinationSize) {
        if (destinationSize > 0) {
            ((uint8_t*) destination)[destinationSize - 1] = BYTE_STUFFING_END;
        }
        return;
    }
    ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_END;
}

/**
 * @brief Writes a byte with byte stuffing.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param byte Byte.
 */
static inline void WriteByte(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const uint8_t byte) {
    switch (byte) {
        case BYTE_STUFFING_END:
            if ((*destinationIndex + 1) >= destinationSize) {
                return;
            }
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC;
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC_END;
            break;
        case BYTE_STUFFING_ESC:
            if ((*destinationIndex + 1) >= destinationSize) {
                return;
            }
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC;
            ((uint8_t*) destination)[(*destinationIndex)++] = BYTE_STUFFING_ESC_ESC;
            break;
        default:
            if (*destinationIndex >= destinationSize) {
                return;
            }
            ((uint8_t*) destination)[(*destinationIndex)++] = byte;
            break;
    }
}

//------------------------------------------------------------------------------
// End of file
