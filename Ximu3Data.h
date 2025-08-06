/**
 * @file Ximu3Data.h
 * @author Seb Madgwick
 * @brief x-IMU3 data messages.
 */

#ifndef XIMU3_DATA_H
#define XIMU3_DATA_H

//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Inertial data message.
 */
typedef struct {
    uint64_t timestamp;
    float gyroscopeX;
    float gyroscopeY;
    float gyroscopeZ;
    float accelerometerX;
    float accelerometerY;
    float accelerometerZ;
} Ximu3DataInertial;

/**
 * @brief Magnetometer data message.
 */
typedef struct {
    uint64_t timestamp;
    float x;
    float y;
    float z;
} Ximu3DataMagnetometer;

/**
 * @brief Quaternion data message.
 */
typedef struct {
    uint64_t timestamp;
    float w;
    float x;
    float y;
    float z;
} Ximu3DataQuaternion;

/**
 * @brief Rotation matrix data message.
 */
typedef struct {
    uint64_t timestamp;
    float xx;
    float xy;
    float xz;
    float yx;
    float yy;
    float yz;
    float zx;
    float zy;
    float zz;
} Ximu3DataRotationMatrix;

/**
 * @brief Euler angles data message.
 */
typedef struct {
    uint64_t timestamp;
    float roll;
    float pitch;
    float yaw;
} Ximu3DataEulerAngles;

/**
 * @brief Linear acceleration data message.
 */
typedef struct {
    uint64_t timestamp;
    float quaternionW;
    float quaternionX;
    float quaternionY;
    float quaternionZ;
    float linearAccelerationX;
    float linearAccelerationY;
    float linearAccelerationZ;
} Ximu3DataLinearAcceleration;

/**
 * @brief Earth acceleration data message.
 */
typedef struct {
    uint64_t timestamp;
    float quaternionW;
    float quaternionX;
    float quaternionY;
    float quaternionZ;
    float earthAccelerationX;
    float earthAccelerationY;
    float earthAccelerationZ;
} Ximu3DataEarthAcceleration;

/**
 * @brief AHRS status data message.
 */
typedef struct {
    uint64_t timestamp;
    bool initialising;
    bool angularRateRecovery;
    bool accelerationRecovery;
    bool magneticRecovery;
} Ximu3DataAhrsStatus;

/**
 * @brief High-g accelerometer data message.
 */
typedef struct {
    uint64_t timestamp;
    float x;
    float y;
    float z;
} Ximu3DataHighGAccelerometer;

/**
 * @brief Temperature data message.
 */
typedef struct {
    uint64_t timestamp;
    float temperature;
} Ximu3DataTemperature;

/**
 * @brief Battery data message.
 */
typedef struct {
    uint64_t timestamp;
    float percentage;
    float voltage;
    float chargingStatus;
} Ximu3DataBattery;

/**
 * @brief RSSI data message.
 */
typedef struct {
    uint64_t timestamp;
    float percentage;
    float power;
} Ximu3DataRssi;

/**
 * @brief Serial accessory data message.
 */
typedef struct {
    uint64_t timestamp;
    const uint8_t* data;
    size_t numberOfBytes;
} Ximu3DataSerialAccessory;

/**
 * @brief Notification data message.
 */
typedef struct {
    uint64_t timestamp;
    const char* string;
} Ximu3DataNotification;

/**
 * @brief Error data message.
 */
typedef struct {
    uint64_t timestamp;
    const char* string;
} Ximu3DataError;

//------------------------------------------------------------------------------
// Function declarations

size_t Ximu3DataInertialBinary(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data);
size_t Ximu3DataInertialAscii(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data);
size_t Ximu3DataMagnetometerBinary(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data);
size_t Ximu3DataMagnetometerAscii(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data);
size_t Ximu3DataQuaternionBinary(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data);
size_t Ximu3DataQuaternionAscii(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data);
size_t Ximu3DataRotationMatrixBinary(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data);
size_t Ximu3DataRotationMatrixAscii(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data);
size_t Ximu3DataEulerAnglesBinary(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data);
size_t Ximu3DataEulerAnglesAscii(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data);
size_t Ximu3DataLinearAccelerationBinary(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data);
size_t Ximu3DataLinearAccelerationAscii(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data);
size_t Ximu3DataEarthAccelerationBinary(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data);
size_t Ximu3DataEarthAccelerationAscii(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data);
size_t Ximu3DataAhrsStatusBinary(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data);
size_t Ximu3DataAhrsStatusAscii(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data);
size_t Ximu3DataHighGAccelerometerBinary(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data);
size_t Ximu3DataHighGAccelerometerAscii(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data);
size_t Ximu3DataTemperatureBinary(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data);
size_t Ximu3DataTemperatureAscii(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data);
size_t Ximu3DataBatteryBinary(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data);
size_t Ximu3DataBatteryAscii(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data);
size_t Ximu3DataRssiBinary(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data);
size_t Ximu3DataRssiAscii(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data);
size_t Ximu3DataSerialAccessoryBinary(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data);
size_t Ximu3DataSerialAccessoryAscii(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data);
size_t Ximu3DataNotificationBinary(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data);
size_t Ximu3DataNotificationAscii(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data);
size_t Ximu3DataErrorBinary(void* const destination, const size_t destinationSize, const Ximu3DataError * const data);
size_t Ximu3DataErrorAscii(void* const destination, const size_t destinationSize, const Ximu3DataError * const data);

#endif

//------------------------------------------------------------------------------
// End of file
