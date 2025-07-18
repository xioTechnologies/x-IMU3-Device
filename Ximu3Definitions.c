// This file was generated by generate.py

#include "Ximu3Definitions.h"

Ximu3Result Ximu3SettingsIndexFrom(Ximu3SettingsIndex * const index, const int integer) {
    switch (integer) {
        case Ximu3SettingsIndexSerialNumber:
            *index = Ximu3SettingsIndexSerialNumber;
            break;
        case Ximu3SettingsIndexCalibrationDate:
            *index = Ximu3SettingsIndexCalibrationDate;
            break;
        case Ximu3SettingsIndexOffset:
            *index = Ximu3SettingsIndexOffset;
            break;
        case Ximu3SettingsIndexSensitivity:
            *index = Ximu3SettingsIndexSensitivity;
            break;
        case Ximu3SettingsIndexFirmwareVersion:
            *index = Ximu3SettingsIndexFirmwareVersion;
            break;
        case Ximu3SettingsIndexDeviceName:
            *index = Ximu3SettingsIndexDeviceName;
            break;
        case Ximu3SettingsIndexBinaryMode:
            *index = Ximu3SettingsIndexBinaryMode;
            break;
        case Ximu3SettingsIndexMessageRateDivisor:
            *index = Ximu3SettingsIndexMessageRateDivisor;
            break;
        default:
            return Ximu3ResultError;
    }
    return Ximu3ResultOk;
}
