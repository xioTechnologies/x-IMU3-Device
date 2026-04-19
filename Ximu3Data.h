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
 * @brief High-g accelerometer data message.
 */
typedef struct {
    uint64_t timestamp;
    float x;
    float y;
    float z;
} Ximu3DataHighGAccelerometer;

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
 * @brief Serial accessory data message.
 */
typedef struct {
    uint64_t timestamp;
    const uint8_t* data;
    size_t numberOfBytes;
} Ximu3DataSerialAccessory;

/**
 * @brief Sync data message.
 */
typedef struct {
    uint64_t timestamp;
    bool edge;
} Ximu3DataSync;

/**
 * @brief LTC data message.
 */
typedef struct {
    uint64_t timestamp;
    const char* timecode;
} Ximu3DataLtc;

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
 * @brief Button data message.
 */
typedef struct {
    uint64_t timestamp;
    bool state;
} Ximu3DataButton;

/**
 * @brief Notification data message.
 */
typedef struct {
    uint64_t timestamp;
    const char* notification;
} Ximu3DataNotification;

/**
 * @brief Error data message.
 */
typedef struct {
    uint64_t timestamp;
    const char* error;
} Ximu3DataError;

#endif

//------------------------------------------------------------------------------
// End of file
