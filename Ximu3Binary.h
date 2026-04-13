/**
 * @file Ximu3Binary.h
 * @author Seb Madgwick
 * @brief x-IMU3 binary data messages.
 */

#ifndef XIMU3_BINARY_H
#define XIMU3_BINARY_H

//------------------------------------------------------------------------------
// Includes

#include <stddef.h>
#include "Ximu3Data.h"

//------------------------------------------------------------------------------
// Function declarations

size_t Ximu3BinaryInertial(void* const destination, const size_t destinationSize, const Ximu3DataInertial * const data);
size_t Ximu3BinaryMagnetometer(void* const destination, const size_t destinationSize, const Ximu3DataMagnetometer * const data);
size_t Ximu3BinaryHighGAccelerometer(void* const destination, const size_t destinationSize, const Ximu3DataHighGAccelerometer * const data);
size_t Ximu3BinaryQuaternion(void* const destination, const size_t destinationSize, const Ximu3DataQuaternion * const data);
size_t Ximu3BinaryRotationMatrix(void* const destination, const size_t destinationSize, const Ximu3DataRotationMatrix * const data);
size_t Ximu3BinaryEulerAngles(void* const destination, const size_t destinationSize, const Ximu3DataEulerAngles * const data);
size_t Ximu3BinaryLinearAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataLinearAcceleration * const data);
size_t Ximu3BinaryEarthAcceleration(void* const destination, const size_t destinationSize, const Ximu3DataEarthAcceleration * const data);
size_t Ximu3BinaryAhrsStatus(void* const destination, const size_t destinationSize, const Ximu3DataAhrsStatus * const data);
size_t Ximu3BinarySerialAccessory(void* const destination, const size_t destinationSize, const Ximu3DataSerialAccessory * const data);
size_t Ximu3BinaryTemperature(void* const destination, const size_t destinationSize, const Ximu3DataTemperature * const data);
size_t Ximu3BinaryBattery(void* const destination, const size_t destinationSize, const Ximu3DataBattery * const data);
size_t Ximu3BinaryRssi(void* const destination, const size_t destinationSize, const Ximu3DataRssi * const data);
size_t Ximu3BinaryNotification(void* const destination, const size_t destinationSize, const Ximu3DataNotification * const data);
size_t Ximu3BinaryError(void* const destination, const size_t destinationSize, const Ximu3DataError * const data);

#endif

//------------------------------------------------------------------------------
// End of file
