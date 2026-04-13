/**
 * @file Test.c
 * @author Seb Madgwick
 * @brief Test.
 */

//------------------------------------------------------------------------------
// Includes

#include <float.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Test.h"
#include "Ximu3.h"

//------------------------------------------------------------------------------
// Function declarations

static void TestAsciiTimestamp(const uint64_t timestamp);

static void TestAsciiFloat(const float floatValue);

static void TestAsciiFloatString(const float floatValue, const char *const floatString);

static void TestAsciiTimestampAndFloat(const uint64_t timestamp, const float floatValue, const char *const floatString);

//------------------------------------------------------------------------------
// Variables

static int passCount = 0;
static int failCount = 0;

//------------------------------------------------------------------------------
// Functions

int Test(void) {
    TestAsciiTimestamp(UINT64_C(0));

    TestAsciiTimestamp(UINT64_C(1));
    TestAsciiTimestamp(UINT64_C(10));
    TestAsciiTimestamp(UINT64_C(100));
    TestAsciiTimestamp(UINT64_C(1000));
    TestAsciiTimestamp(UINT64_C(10000));
    TestAsciiTimestamp(UINT64_C(100000));
    TestAsciiTimestamp(UINT64_C(1000000));
    TestAsciiTimestamp(UINT64_C(10000000));
    TestAsciiTimestamp(UINT64_C(100000000));
    TestAsciiTimestamp(UINT64_C(1000000000));
    TestAsciiTimestamp(UINT64_C(10000000000));
    TestAsciiTimestamp(UINT64_C(100000000000));
    TestAsciiTimestamp(UINT64_C(1000000000000));
    TestAsciiTimestamp(UINT64_C(10000000000000));
    TestAsciiTimestamp(UINT64_C(100000000000000));
    TestAsciiTimestamp(UINT64_C(1000000000000000));
    TestAsciiTimestamp(UINT64_C(10000000000000000));
    TestAsciiTimestamp(UINT64_C(100000000000000000));
    TestAsciiTimestamp(UINT64_C(1000000000000000000));

    TestAsciiTimestamp(UINT64_C(12));
    TestAsciiTimestamp(UINT64_C(123));
    TestAsciiTimestamp(UINT64_C(1234));
    TestAsciiTimestamp(UINT64_C(12345));
    TestAsciiTimestamp(UINT64_C(123456));
    TestAsciiTimestamp(UINT64_C(1234567));
    TestAsciiTimestamp(UINT64_C(12345678));
    TestAsciiTimestamp(UINT64_C(123456789));
    TestAsciiTimestamp(UINT64_C(1234567890));
    TestAsciiTimestamp(UINT64_C(12345678901));
    TestAsciiTimestamp(UINT64_C(123456789012));
    TestAsciiTimestamp(UINT64_C(1234567890123));
    TestAsciiTimestamp(UINT64_C(12345678901234));
    TestAsciiTimestamp(UINT64_C(123456789012345));
    TestAsciiTimestamp(UINT64_C(1234567890123456));
    TestAsciiTimestamp(UINT64_C(12345678901234567));
    TestAsciiTimestamp(UINT64_C(123456789012345678));
    TestAsciiTimestamp(UINT64_C(1234567890123456789));

    TestAsciiTimestamp(UINT64_C(99));
    TestAsciiTimestamp(UINT64_C(999));
    TestAsciiTimestamp(UINT64_C(9999));
    TestAsciiTimestamp(UINT64_C(99999));
    TestAsciiTimestamp(UINT64_C(999999));
    TestAsciiTimestamp(UINT64_C(9999999));
    TestAsciiTimestamp(UINT64_C(99999999));
    TestAsciiTimestamp(UINT64_C(999999999));
    TestAsciiTimestamp(UINT64_C(9999999999));
    TestAsciiTimestamp(UINT64_C(99999999999));
    TestAsciiTimestamp(UINT64_C(999999999999));
    TestAsciiTimestamp(UINT64_C(9999999999999));
    TestAsciiTimestamp(UINT64_C(99999999999999));
    TestAsciiTimestamp(UINT64_C(999999999999999));
    TestAsciiTimestamp(UINT64_C(9999999999999999));
    TestAsciiTimestamp(UINT64_C(99999999999999999));
    TestAsciiTimestamp(UINT64_C(999999999999999999));
    TestAsciiTimestamp(UINT64_C(9999999999999999999));

    TestAsciiTimestamp(UINT64_MAX);

    TestAsciiFloat(0.0f);

    TestAsciiFloat(-0.0001f);
    TestAsciiFloat(-0.0010f);
    TestAsciiFloat(-0.0100f);
    TestAsciiFloat(-0.1000f);
    TestAsciiFloat(-1.0000f);
    TestAsciiFloat(-10.0000f);
    TestAsciiFloat(-100.0000f);
    TestAsciiFloat(-1000.0000f);
    TestAsciiFloat(-10000.0000f);
    TestAsciiFloat(-100000.0000f);

    TestAsciiFloat(0.0001f);
    TestAsciiFloat(0.0010f);
    TestAsciiFloat(0.0100f);
    TestAsciiFloat(0.1000f);
    TestAsciiFloat(1.0000f);
    TestAsciiFloat(10.0000f);
    TestAsciiFloat(100.0000f);
    TestAsciiFloat(1000.0000f);
    TestAsciiFloat(10000.0000f);
    TestAsciiFloat(100000.0000f);

    TestAsciiFloat(-0.0012f);
    TestAsciiFloat(-0.0123f);
    TestAsciiFloat(-0.1234f);
    TestAsciiFloat(-1.2345f);
    TestAsciiFloat(-12.3456f);
    TestAsciiFloat(-123.4567f);
    TestAsciiFloat(-1234.5678f);
    TestAsciiFloat(-12345.6789f);
    TestAsciiFloat(-123456.7890f);

    TestAsciiFloat(0.0012f);
    TestAsciiFloat(0.0123f);
    TestAsciiFloat(0.1234f);
    TestAsciiFloat(1.2345f);
    TestAsciiFloat(12.3456f);
    TestAsciiFloat(123.4567f);
    TestAsciiFloat(1234.5678f);
    TestAsciiFloat(12345.6789f);
    TestAsciiFloat(123456.7890f);

    TestAsciiFloat(-0.0005f);
    TestAsciiFloat(-0.0050f);
    TestAsciiFloat(-0.0500f);
    TestAsciiFloat(-0.5000f);
    TestAsciiFloat(-5.0000f);
    TestAsciiFloat(-50.0000f);
    TestAsciiFloat(-500.0000f);
    TestAsciiFloat(-5000.0000f);
    TestAsciiFloat(-50000.0000f);
    TestAsciiFloat(-500000.0000f);

    TestAsciiFloat(0.0005f);
    TestAsciiFloat(0.0050f);
    TestAsciiFloat(0.0500f);
    TestAsciiFloat(0.5000f);
    TestAsciiFloat(5.0000f);
    TestAsciiFloat(50.0000f);
    TestAsciiFloat(500.0000f);
    TestAsciiFloat(5000.0000f);
    TestAsciiFloat(50000.0000f);
    TestAsciiFloat(500000.0000f);

    TestAsciiFloat(-0.0099f);
    TestAsciiFloat(-0.0999f);
    TestAsciiFloat(-0.9999f);
    TestAsciiFloat(-9.9999f);
    TestAsciiFloat(-99.9999f);
    TestAsciiFloat(-999.9999f);
    TestAsciiFloat(-9999.9999f);
    TestAsciiFloat(-99999.9999f);
    TestAsciiFloatString(-999999.9999f, "-999999.9999"); // -999999.9999f rounds to -1000000.0f due to floating-point precision

    TestAsciiFloat(0.0099f);
    TestAsciiFloat(0.0999f);
    TestAsciiFloat(0.9999f);
    TestAsciiFloat(9.9999f);
    TestAsciiFloat(99.9999f);
    TestAsciiFloat(999.9999f);
    TestAsciiFloat(9999.9999f);
    TestAsciiFloat(99999.9999f);
    TestAsciiFloatString(999999.9999f, "999999.9999"); // 999999.9999f rounds to 1000000.0f due to floating-point precision

    TestAsciiFloatString(-0.0f, "0.0000");

    TestAsciiFloatString(-1000000.0f, "-999999.9999");
    TestAsciiFloatString(1000000.0f, "999999.9999");

    TestAsciiFloat(FLT_MIN);
    TestAsciiFloatString(-FLT_MAX, "-999999.9999");
    TestAsciiFloatString(FLT_MAX, "999999.9999");

    printf("Passed %d of %d\n", passCount, passCount + failCount);

    return failCount > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

static void TestAsciiTimestamp(const uint64_t timestamp) {
    TestAsciiTimestampAndFloat(timestamp, 0.0f, NULL);
}

static void TestAsciiFloat(const float floatValue) {
    TestAsciiTimestampAndFloat(UINT64_C(0), floatValue, NULL);
}

static void TestAsciiFloatString(const float floatValue, const char *const floatString) {
    TestAsciiTimestampAndFloat(UINT64_C(0), floatValue, floatString);
}

static void TestAsciiTimestampAndFloat(const uint64_t timestamp, const float floatValue, const char *const floatString) {
    char expected[256];
    if (floatString == NULL) {
        snprintf(expected, sizeof(expected), "T,%" PRIu64 ",%.4f\n", timestamp, (double) floatValue);
    } else {
        snprintf(expected, sizeof(expected), "T,%" PRIu64 ",%s\n", timestamp, floatString);
    }

    char actual[256];
    const Ximu3DataTemperature data = {
        .timestamp = timestamp,
        .temperature = floatValue,
    };
    const size_t messageSize = Ximu3AsciiTemperature(actual, sizeof(actual), &data);
    actual[messageSize] = '\0';

    if (strcmp(actual, expected) != 0) {
        failCount++;
        printf("Failed\n");
        printf("\tExpected: %s", expected);
        printf("\tActual:   %s", actual);
    } else {
        passCount++;
    }
}

//------------------------------------------------------------------------------
// End of file
