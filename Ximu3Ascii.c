/**
 * @file Ximu3Ascii.c
 * @author Seb Madgwick
 * @brief x-IMU3 ASCII data messages.
 */

//------------------------------------------------------------------------------
// Includes

#include "Ximu3Ascii.h"
#include "Ximu3Definitions.h"

//------------------------------------------------------------------------------
// Function declarations

static inline void WriteHeader(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char asciiId, const uint64_t timestamp);
static inline void WriteFloat(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const float value);
static inline void WriteString(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char* string);
static inline void WriteTermination(void* const destination, const size_t destinationSize, size_t * const destinationIndex);
static inline void WriteChar(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char character);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Writes an ASCII inertial data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiInertial(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data) {
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
 * @brief Writes an ASCII magnetometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiMagnetometer(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_MAGNETOMETER, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->x);
    WriteFloat(destination, destinationSize, &destinationIndex, data->y);
    WriteFloat(destination, destinationSize, &destinationIndex, data->z);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII high-g accelerometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiHighGAccelerometer(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_HIGH_G_ACCELEROMETER, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->x);
    WriteFloat(destination, destinationSize, &destinationIndex, data->y);
    WriteFloat(destination, destinationSize, &destinationIndex, data->z);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII quaternion data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiQuaternion(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data) {
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
 * @brief Writes an ASCII rotation matrix data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiRotationMatrix(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data) {
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
 * @brief Writes an ASCII Euler angles data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiEulerAngles(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_EULER_ANGLES, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->roll);
    WriteFloat(destination, destinationSize, &destinationIndex, data->pitch);
    WriteFloat(destination, destinationSize, &destinationIndex, data->yaw);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII linear acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiLinearAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data) {
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
 * @brief Writes an ASCII Earth acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiEarthAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data) {
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
 * @brief Writes an ASCII AHRS status data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiAhrsStatus(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data) {
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
 * @brief Writes an ASCII serial accessory data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiSerialAccessory(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_SERIAL_ACCESSORY, data->timestamp);
    WriteChar(destination, destinationSize, &destinationIndex, ',');
    for (size_t index = 0; index < data->numberOfBytes; index++) {
        const uint8_t byte = data->data[index];
        WriteChar(destination, destinationSize, &destinationIndex, (char) byte);
    }
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII temperature data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiTemperature(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_TEMPERATURE, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->temperature);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII battery data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiBattery(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_BATTERY, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->percentage);
    WriteFloat(destination, destinationSize, &destinationIndex, data->voltage);
    WriteFloat(destination, destinationSize, &destinationIndex, data->chargingStatus);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII RSSI data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiRssi(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_RSSI, data->timestamp);
    WriteFloat(destination, destinationSize, &destinationIndex, data->percentage);
    WriteFloat(destination, destinationSize, &destinationIndex, data->power);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}


/**
 * @brief Writes an ASCII notification data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiNotification(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data) {
    size_t destinationIndex = 0;
    WriteHeader(destination, destinationSize, &destinationIndex, XIMU3_ASCII_ID_NOTIFICATION, data->timestamp);
    WriteString(destination, destinationSize, &destinationIndex, data->notification);
    WriteTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes an ASCII error data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3AsciiError(void* const destination, const size_t destinationSize, const Ximu3DataError * const data) {
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

    // ID
    WriteChar(destination, destinationSize, destinationIndex, asciiId);
    WriteChar(destination, destinationSize, destinationIndex, ',');

    // Timestamp
    if (timestamp == 0) {
        WriteChar(destination, destinationSize, destinationIndex, '0');
        return;
    }
    char reversed[20];
    int length = 0;
    uint64_t quotient = timestamp;
    while (quotient > 0) {
        reversed[length++] = '0' + (char) (quotient % 10); // index will never exceed 19 because UINT64_MAX is 20 digits
        quotient /= 10;
    }
    while (--length >= 0) {
        WriteChar(destination, destinationSize, destinationIndex, reversed[length]);
    }
}

/**
 * @brief Writes a float.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param value Value.
 */
static inline void WriteFloat(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const float value) {

    // Limits
    if (value >= 999999.9999f) {
        WriteString(destination, destinationSize, destinationIndex, "999999.9999");
        return;
    }
    if (value <= -999999.9999f) {
        WriteString(destination, destinationSize, destinationIndex, "-999999.9999");
        return;
    }
    WriteChar(destination, destinationSize, destinationIndex, ',');

    // Sign
    float absolute = value;
    if (value < 0.0f) {
        WriteChar(destination, destinationSize, destinationIndex, '-');
        absolute = -value;
    }

    // Integer part
    const uint32_t integer = (uint32_t) absolute;
    if (integer == 0) {
        WriteChar(destination, destinationSize, destinationIndex, '0');
    } else {
        char reversed[6];
        int length = 0;
        uint32_t quotient = integer;
        while (quotient > 0) {
            reversed[length++] = '0' + (char) (quotient % 10); // index will never exceed 5 because integer is limited to 999999
            quotient /= 10;
        }
        while (--length >= 0) {
            WriteChar(destination, destinationSize, destinationIndex, reversed[length]);
        }
    }

    // Fractional part
    const uint32_t fraction = (uint32_t) (((absolute - (float) integer) * 10000.0f) + 0.5f);
    WriteChar(destination, destinationSize, destinationIndex, '.');
    WriteChar(destination, destinationSize, destinationIndex, '0' + (char) (fraction / 1000));
    WriteChar(destination, destinationSize, destinationIndex, '0' + (char) ((fraction / 100) % 10));
    WriteChar(destination, destinationSize, destinationIndex, '0' + (char) ((fraction / 10) % 10));
    WriteChar(destination, destinationSize, destinationIndex, '0' + (char) (fraction % 10));
}

/**
 * @brief Writes a string.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param string String.
 */
static inline void WriteString(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char* string) {
    WriteChar(destination, destinationSize, destinationIndex, ',');
    while (*string != '\0') {
        WriteChar(destination, destinationSize, destinationIndex, *string++);
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
            ((char*) destination)[destinationSize - 1] = XIMU3_TERMINATION;
        }
        return;
    }
    ((char*) destination)[(*destinationIndex)++] = XIMU3_TERMINATION;
}

/**
 * @brief Writes a character.
 * @param destination Destination.
 * @param destinationIndex Destination index.
 * @param character Character.
 */
static inline void WriteChar(void* const destination, const size_t destinationSize, size_t * const destinationIndex, const char character) {
    if (*destinationIndex >= destinationSize) {
        return;
    }
    if (((unsigned char) character < 0x20) || ((unsigned char) character > 0x7E)) {
        ((char*) destination)[(*destinationIndex)++] = '?';
        return;
    }
    ((char*) destination)[(*destinationIndex)++] = character;
}

//------------------------------------------------------------------------------
// End of file
