/**
 * @file Ximu3Data.c
 * @author Seb Madgwick
 * @brief x-IMU3 data messages.
 */

//------------------------------------------------------------------------------
// Includes

#include "Binary.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include "Ximu3Data.h"

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Float format used by ASCII data messages.
 */
#define FLOAT_FORMAT "%.4f"

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Writes binary inertial data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataInertialBinary(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'I');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->gyroscopeX);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->gyroscopeY);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->gyroscopeZ);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->accelerometerX);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->accelerometerY);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->accelerometerZ);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII inertial data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataInertialAscii(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data) {
    return snprintf(destination, destinationSize, "I,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->gyroscopeX,
            data->gyroscopeY,
            data->gyroscopeZ,
            data->accelerometerX,
            data->accelerometerY,
            data->accelerometerZ);
}

/**
 * @brief Writes binary magnetometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataMagnetometerBinary(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'M');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->x);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->y);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->z);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII magnetometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataMagnetometerAscii(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data) {
    return snprintf(destination, destinationSize, "M,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->x,
            data->y,
            data->z);
}

/**
 * @brief Writes binary quaternion data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataQuaternionBinary(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'Q');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->w);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->x);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->y);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->z);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII quaternion data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataQuaternionAscii(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data) {
    return snprintf(destination, destinationSize, "Q,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->w,
            data->x,
            data->y,
            data->z);
}

/**
 * @brief Writes binary rotation matrix data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataRotationMatrixBinary(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'R');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->xx);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->xy);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->xz);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->yx);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->yy);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->yz);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->zx);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->zy);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->zz);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII rotation matrix data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataRotationMatrixAscii(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data) {
    return snprintf(destination, destinationSize, "R,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->xx,
            data->xy,
            data->xz,
            data->yx,
            data->yy,
            data->yz,
            data->zx,
            data->zy,
            data->zz);
}

/**
 * @brief Writes binary Euler angles data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataEulerAnglesBinary(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'A');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->roll);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->pitch);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->yaw);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII Euler angles data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataEulerAnglesAscii(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data) {
    return snprintf(destination, destinationSize, "A,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->roll,
            data->pitch,
            data->yaw);
}

/**
 * @brief Writes binary linear acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataLinearAccelerationBinary(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'L');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionW);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionX);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionY);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionZ);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->linearAccelerationX);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->linearAccelerationY);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->linearAccelerationZ);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII linear acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataLinearAccelerationAscii(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data) {
    return snprintf(destination, destinationSize, "L,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->quaternionW,
            data->quaternionX,
            data->quaternionY,
            data->quaternionZ,
            data->linearAccelerationX,
            data->linearAccelerationY,
            data->linearAccelerationZ);
}

/**
 * @brief Writes binary Earth acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataEarthAccelerationBinary(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'E');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionW);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionX);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionY);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->quaternionZ);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->earthAccelerationX);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->earthAccelerationY);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->earthAccelerationZ);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII Earth acceleration data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataEarthAccelerationAscii(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data) {
    return snprintf(destination, destinationSize, "E,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->quaternionW,
            data->quaternionX,
            data->quaternionY,
            data->quaternionZ,
            data->earthAccelerationX,
            data->earthAccelerationY,
            data->earthAccelerationZ);
}

/**
 * @brief Writes binary AHRS status data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataAhrsStatusBinary(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'U');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, (float) data->initialising);
    BinaryFloat(destination, destinationSize, &destinationIndex, (float) data->angularRateRecovery);
    BinaryFloat(destination, destinationSize, &destinationIndex, (float) data->accelerationRecovery);
    BinaryFloat(destination, destinationSize, &destinationIndex, (float) data->magneticRecovery);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII AHRS status data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataAhrsStatusAscii(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data) {
    return snprintf(destination, destinationSize, "U,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            (float) data->initialising,
            (float) data->angularRateRecovery,
            (float) data->accelerationRecovery,
            (float) data->magneticRecovery);
}

/**
 * @brief Writes binary high-g accelerometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataHighGAccelerometerBinary(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'H');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->x);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->y);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->z);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII high-g accelerometer data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataHighGAccelerometerAscii(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data) {
    return snprintf(destination, destinationSize, "H,%" PRIu64 ","
            FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->x,
            data->y,
            data->z);
}

/**
 * @brief Writes binary temperature data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataTemperatureBinary(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'T');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->temperature);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII temperature data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataTemperatureAscii(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data) {
    return snprintf(destination, destinationSize, "T,%" PRIu64 "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->temperature);
}

/**
 * @brief Writes binary battery data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataBatteryBinary(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'B');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->percentage);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->voltage);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->chargingStatus);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII battery data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataBatteryAscii(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data) {
    return snprintf(destination, destinationSize, "B,%" PRIu64 "," FLOAT_FORMAT "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->percentage,
            data->voltage,
            data->chargingStatus);
}

/**
 * @brief Writes binary RSSI data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataRssiBinary(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'W');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->percentage);
    BinaryFloat(destination, destinationSize, &destinationIndex, data->power);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII RSSI data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataRssiAscii(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data) {
    return snprintf(destination, destinationSize, "W,%" PRIu64 "," FLOAT_FORMAT "," FLOAT_FORMAT "\n",
            data->timestamp,
            data->percentage,
            data->power);
}

/**
 * @brief Writes binary serial accessory data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataSerialAccessoryBinary(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'S');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    for (size_t index = 0; index < data->numberOfBytes; index++) {
        BinaryWrite(destination, destinationSize, &destinationIndex, data->data[index]);
    }
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII serial accessory data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataSerialAccessoryAscii(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data) {
    size_t destinationIndex = snprintf(destination, destinationSize, "S,%" PRIu64 ",", data->timestamp);
    for (size_t index = 0; index < data->numberOfBytes; index++) {
        const uint8_t byte = data->data[index];
        ((uint8_t*) destination)[destinationIndex++] = ((char) byte < 0) || (isprint(byte) == 0) ? '?' : byte;
    }
    ((uint8_t*) destination)[destinationIndex++] = '\n';
    return destinationIndex;
}

/**
 * @brief Writes binary notification data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataNotificationBinary(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'N');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryString(destination, destinationSize, &destinationIndex, data->string);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII notification data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataNotificationAscii(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data) {
    return snprintf(destination, destinationSize, "N,%" PRIu64 ",%s\n", data->timestamp, data->string);
}

/**
 * @brief Writes binary error data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataErrorBinary(void* const destination, const size_t destinationSize, const Ximu3DataError * const data) {
    size_t destinationIndex = 0;
    BinaryFirstByte(destination, destinationSize, &destinationIndex, 'F');
    BinaryTimestamp(destination, destinationSize, &destinationIndex, data->timestamp);
    BinaryString(destination, destinationSize, &destinationIndex, data->string);
    BinaryTermination(destination, destinationSize, &destinationIndex);
    return destinationIndex;
}

/**
 * @brief Writes ASCII error data message.
 * @param destination Destination.
 * @param destinationSize Destination size.
 * @param data Data.
 * @return Message size.
 */
size_t Ximu3DataErrorAscii(void* const destination, const size_t destinationSize, const Ximu3DataError * const data) {
    return snprintf(destination, destinationSize, "F,%" PRIu64 ",%s\n", data->timestamp, data->string);
}

//------------------------------------------------------------------------------
// End of file
