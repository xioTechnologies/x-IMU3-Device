/**
 * @file Ximu3Ascii.h
 * @author Seb Madgwick
 * @brief x-IMU3 ASCII data messages.
 */

#ifndef XIMU3_ASCII_H
#define XIMU3_ASCII_H

//------------------------------------------------------------------------------
// Includes

#include <stddef.h>
#include "Ximu3Data.h"

//------------------------------------------------------------------------------
// Definitions

#define XIMU3_ASCII_ID_INERTIAL             'I'
#define XIMU3_ASCII_ID_MAGNETOMETER         'M'
#define XIMU3_ASCII_ID_HIGH_G_ACCELEROMETER 'H'
#define XIMU3_ASCII_ID_QUATERNION           'Q'
#define XIMU3_ASCII_ID_ROTATION_MATRIX      'R'
#define XIMU3_ASCII_ID_EULER_ANGLES         'A'
#define XIMU3_ASCII_ID_LINEAR_ACCELERATION  'L'
#define XIMU3_ASCII_ID_EARTH_ACCELERATION   'E'
#define XIMU3_ASCII_ID_AHRS_STATUS          'U'
#define XIMU3_ASCII_ID_SERIAL_ACCESSORY     'S'
#define XIMU3_ASCII_ID_SYNC                 'Y'
#define XIMU3_ASCII_ID_LTC                  'C'
#define XIMU3_ASCII_ID_TEMPERATURE          'T'
#define XIMU3_ASCII_ID_BATTERY              'B'
#define XIMU3_ASCII_ID_RSSI                 'W'
#define XIMU3_ASCII_ID_BUTTON               'O'
#define XIMU3_ASCII_ID_NOTIFICATION         'N'
#define XIMU3_ASCII_ID_ERROR                'F'

//------------------------------------------------------------------------------
// Function declarations

size_t Ximu3AsciiInertial(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data);
size_t Ximu3AsciiMagnetometer(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data);
size_t Ximu3AsciiHighGAccelerometer(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data);
size_t Ximu3AsciiQuaternion(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data);
size_t Ximu3AsciiRotationMatrix(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data);
size_t Ximu3AsciiEulerAngles(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data);
size_t Ximu3AsciiLinearAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data);
size_t Ximu3AsciiEarthAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data);
size_t Ximu3AsciiAhrsStatus(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data);
size_t Ximu3AsciiSerialAccessory(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data);
size_t Ximu3AsciiSync(void* const destination, const size_t destinationSize, const Ximu3DataSync * const data);
size_t Ximu3AsciiLtc(void* const destination, const size_t destinationSize, const Ximu3DataLtc * const data);
size_t Ximu3AsciiTemperature(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data);
size_t Ximu3AsciiBattery(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data);
size_t Ximu3AsciiRssi(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data);
size_t Ximu3AsciiButton(void* const destination, const size_t destinationSize, const Ximu3DataButton * const data);
size_t Ximu3AsciiNotification(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data);
size_t Ximu3AsciiError(void* const destination, const size_t destinationSize, const Ximu3DataError * const data);

#endif

//------------------------------------------------------------------------------
// End of file
