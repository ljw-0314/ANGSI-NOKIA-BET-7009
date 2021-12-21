// binary representation
// attribute size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef _LE_MI_SERVER_H
#define _LE_MI_SERVER_H

#include <stdint.h>
//
// gatt profile include file, generated by jieli gatt_inc_generator.exe
//

const uint8_t profile_data[] = {
    //////////////////////////////////////////////////////
    //
    // 0x0001 PRIMARY_SERVICE  1800
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18,

    /* CHARACTERISTIC,  2a00, READ | DYNAMIC, */
    // 0x0002 CHARACTERISTIC 2a00 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a,
    // 0x0003 VALUE 2a00 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00, 0x2a,

    /* CHARACTERISTIC,  2a01, READ | DYNAMIC, */
    // 0x0004 CHARACTERISTIC 2a01 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x04, 0x00, 0x03, 0x28, 0x02, 0x05, 0x00, 0x01, 0x2a,
    // 0x0005 VALUE 2a01 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x05, 0x00, 0x01, 0x2a,

    /* CHARACTERISTIC,  2a04, READ | DYNAMIC, */
    // 0x0006 CHARACTERISTIC 2a04 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x06, 0x00, 0x03, 0x28, 0x02, 0x07, 0x00, 0x04, 0x2a,
    // 0x0007 VALUE 2a04 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x07, 0x00, 0x04, 0x2a,

    //////////////////////////////////////////////////////
    //
    // 0x0008 PRIMARY_SERVICE  1801
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x28, 0x01, 0x18,

    /* CHARACTERISTIC,  2a05, INDICATE, */
    // 0x0009 CHARACTERISTIC 2a05 INDICATE
    0x0d, 0x00, 0x02, 0x00, 0x09, 0x00, 0x03, 0x28, 0x20, 0x0a, 0x00, 0x05, 0x2a,
    // 0x000a VALUE 2a05 INDICATE
    0x08, 0x00, 0x20, 0x00, 0x0a, 0x00, 0x05, 0x2a,
    // 0x000b CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x0b, 0x00, 0x02, 0x29, 0x00, 0x00,

    //////////////////////////////////////////////////////
    //
    // 0x000c PRIMARY_SERVICE  af00
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x00, 0x28, 0x00, 0xaf,

    /* CHARACTERISTIC,  af01, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x000d CHARACTERISTIC af01 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x0d, 0x00, 0x03, 0x28, 0x04, 0x0e, 0x00, 0x01, 0xaf,
    // 0x000e VALUE af01 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x0e, 0x00, 0x01, 0xaf,

    /* CHARACTERISTIC,  af02, NOTIFY, */
    // 0x000f CHARACTERISTIC af02 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x0f, 0x00, 0x03, 0x28, 0x10, 0x10, 0x00, 0x02, 0xaf,
    // 0x0010 VALUE af02 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x10, 0x00, 0x02, 0xaf,
    // 0x0011 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x11, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  af03, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0012 CHARACTERISTIC af03 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x12, 0x00, 0x03, 0x28, 0x04, 0x13, 0x00, 0x03, 0xaf,
    // 0x0013 VALUE af03 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x13, 0x00, 0x03, 0xaf,

    /* CHARACTERISTIC,  af04, NOTIFY, */
    // 0x0014 CHARACTERISTIC af04 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x14, 0x00, 0x03, 0x28, 0x10, 0x15, 0x00, 0x04, 0xaf,
    // 0x0015 VALUE af04 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x15, 0x00, 0x04, 0xaf,
    // 0x0016 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x16, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  af05, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0017 CHARACTERISTIC af05 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x17, 0x00, 0x03, 0x28, 0x04, 0x18, 0x00, 0x05, 0xaf,
    // 0x0018 VALUE af05 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x18, 0x00, 0x05, 0xaf,

    /* CHARACTERISTIC,  af06, NOTIFY, */
    // 0x0019 CHARACTERISTIC af06 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x19, 0x00, 0x03, 0x28, 0x10, 0x1a, 0x00, 0x06, 0xaf,
    // 0x001a VALUE af06 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x1a, 0x00, 0x06, 0xaf,
    // 0x001b CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x1b, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  af07, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x001c CHARACTERISTIC af07 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x1c, 0x00, 0x03, 0x28, 0x04, 0x1d, 0x00, 0x07, 0xaf,
    // 0x001d VALUE af07 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x1d, 0x00, 0x07, 0xaf,

    /* CHARACTERISTIC,  af08, NOTIFY, */
    // 0x001e CHARACTERISTIC af08 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x1e, 0x00, 0x03, 0x28, 0x10, 0x1f, 0x00, 0x08, 0xaf,
    // 0x001f VALUE af08 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x1f, 0x00, 0x08, 0xaf,
    // 0x0020 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x20, 0x00, 0x02, 0x29, 0x00, 0x00,

    //////////////////////////////////////////////////////
    //
    // 0x0021 PRIMARY_SERVICE  180a
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x21, 0x00, 0x00, 0x28, 0x0a, 0x18,

    /* CHARACTERISTIC,  2a29, READ | DYNAMIC, */
    // 0x0022 CHARACTERISTIC 2a29 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x22, 0x00, 0x03, 0x28, 0x02, 0x23, 0x00, 0x29, 0x2a,
    // 0x0023 VALUE 2a29 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x23, 0x00, 0x29, 0x2a,

    /* CHARACTERISTIC,  2a24, READ | DYNAMIC, */
    // 0x0024 CHARACTERISTIC 2a24 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x24, 0x00, 0x03, 0x28, 0x02, 0x25, 0x00, 0x24, 0x2a,
    // 0x0025 VALUE 2a24 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x25, 0x00, 0x24, 0x2a,

    /* CHARACTERISTIC,  2a25, READ | DYNAMIC, */
    // 0x0026 CHARACTERISTIC 2a25 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x26, 0x00, 0x03, 0x28, 0x02, 0x27, 0x00, 0x25, 0x2a,
    // 0x0027 VALUE 2a25 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x27, 0x00, 0x25, 0x2a,

    /* CHARACTERISTIC,  2a27, READ | DYNAMIC, */
    // 0x0028 CHARACTERISTIC 2a27 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x28, 0x00, 0x03, 0x28, 0x02, 0x29, 0x00, 0x27, 0x2a,
    // 0x0029 VALUE 2a27 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x29, 0x00, 0x27, 0x2a,

    /* CHARACTERISTIC,  2a26, READ | DYNAMIC, */
    // 0x002a CHARACTERISTIC 2a26 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x2a, 0x00, 0x03, 0x28, 0x02, 0x2b, 0x00, 0x26, 0x2a,
    // 0x002b VALUE 2a26 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x2b, 0x00, 0x26, 0x2a,

    /* CHARACTERISTIC,  2a28, READ | DYNAMIC, */
    // 0x002c CHARACTERISTIC 2a28 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x2c, 0x00, 0x03, 0x28, 0x02, 0x2d, 0x00, 0x28, 0x2a,
    // 0x002d VALUE 2a28 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x2d, 0x00, 0x28, 0x2a,

    /* CHARACTERISTIC,  2a23, READ | DYNAMIC, */
    // 0x002e CHARACTERISTIC 2a23 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x2e, 0x00, 0x03, 0x28, 0x02, 0x2f, 0x00, 0x23, 0x2a,
    // 0x002f VALUE 2a23 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x2f, 0x00, 0x23, 0x2a,

    /* CHARACTERISTIC,  2a2a, READ | DYNAMIC, */
    // 0x0030 CHARACTERISTIC 2a2a READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x30, 0x00, 0x03, 0x28, 0x02, 0x31, 0x00, 0x2a, 0x2a,
    // 0x0031 VALUE 2a2a READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x31, 0x00, 0x2a, 0x2a,

    /* CHARACTERISTIC,  2a50, READ | AUTHENTICATION_REQUIRED | DYNAMIC, */
    // 0x0032 CHARACTERISTIC 2a50 READ | AUTHENTICATION_REQUIRED | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x32, 0x00, 0x03, 0x28, 0x02, 0x33, 0x00, 0x50, 0x2a,
    // 0x0033 VALUE 2a50 READ | AUTHENTICATION_REQUIRED | DYNAMIC
    0x08, 0x00, 0x02, 0x05, 0x33, 0x00, 0x50, 0x2a,

    //////////////////////////////////////////////////////
    //
    // 0x0034 PRIMARY_SERVICE  180f
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x34, 0x00, 0x00, 0x28, 0x0f, 0x18,

    /* CHARACTERISTIC,  2a19, READ | DYNAMIC | NOTIFY, */
    // 0x0035 CHARACTERISTIC 2a19 READ | DYNAMIC | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x35, 0x00, 0x03, 0x28, 0x12, 0x36, 0x00, 0x19, 0x2a,
    // 0x0036 VALUE 2a19 READ | DYNAMIC | NOTIFY
    0x08, 0x00, 0x12, 0x01, 0x36, 0x00, 0x19, 0x2a,
    // 0x0037 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x37, 0x00, 0x02, 0x29, 0x00, 0x00,
#if 0
    //////////////////////////////////////////////////////
    //
    // 0x0038 PRIMARY_SERVICE  1812
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x38, 0x00, 0x00, 0x28, 0x12, 0x18,

    /* CHARACTERISTIC,  2a4e, READ | WRITE_WITHOUT_RESPONSE,01 */
    // 0x0039 CHARACTERISTIC 2a4e READ | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x39, 0x00, 0x03, 0x28, 0x06, 0x3a, 0x00, 0x4e, 0x2a,
    // 0x003a VALUE 2a4e READ | WRITE_WITHOUT_RESPONSE 01
    0x09, 0x00, 0x06, 0x00, 0x3a, 0x00, 0x4e, 0x2a, 0x01,

    /* CHARACTERISTIC,  2a4d, READ | WRITE | NOTIFY, */
    // 0x003b CHARACTERISTIC 2a4d READ | WRITE | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x3b, 0x00, 0x03, 0x28, 0x1a, 0x3c, 0x00, 0x4d, 0x2a,
    // 0x003c VALUE 2a4d READ | WRITE | NOTIFY
    0x08, 0x00, 0x1a, 0x00, 0x3c, 0x00, 0x4d, 0x2a,
    // 0x003d CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x3d, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* 0x003e REPORT_REFERENCE,01,01 */
    0x0a, 0x00, 0x02, 0x00, 0x3e, 0x00, 0x08, 0x29, 0x01, 0x01,

    /* CHARACTERISTIC,  2a4d, READ | WRITE | NOTIFY, */
    // 0x003f CHARACTERISTIC 2a4d READ | WRITE | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x3f, 0x00, 0x03, 0x28, 0x1a, 0x40, 0x00, 0x4d, 0x2a,
    // 0x0040 VALUE 2a4d READ | WRITE | NOTIFY
    0x08, 0x00, 0x1a, 0x00, 0x40, 0x00, 0x4d, 0x2a,
    // 0x0041 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x41, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* 0x0042 REPORT_REFERENCE,02,01 */
    0x0a, 0x00, 0x02, 0x00, 0x42, 0x00, 0x08, 0x29, 0x02, 0x01,

    /* CHARACTERISTIC,  2a4d, READ | WRITE | NOTIFY, */
    // 0x0043 CHARACTERISTIC 2a4d READ | WRITE | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x43, 0x00, 0x03, 0x28, 0x1a, 0x44, 0x00, 0x4d, 0x2a,
    // 0x0044 VALUE 2a4d READ | WRITE | NOTIFY
    0x08, 0x00, 0x1a, 0x00, 0x44, 0x00, 0x4d, 0x2a,
    // 0x0045 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x45, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* 0x0046 REPORT_REFERENCE,03,01 */
    0x0a, 0x00, 0x02, 0x00, 0x46, 0x00, 0x08, 0x29, 0x03, 0x01,

    /* CHARACTERISTIC,  2a4d, READ | WRITE, */
    // 0x0047 CHARACTERISTIC 2a4d READ | WRITE
    0x0d, 0x00, 0x02, 0x00, 0x47, 0x00, 0x03, 0x28, 0x0a, 0x48, 0x00, 0x4d, 0x2a,
    // 0x0048 VALUE 2a4d READ | WRITE
    0x08, 0x00, 0x0a, 0x00, 0x48, 0x00, 0x4d, 0x2a,

    /* 0x0049 REPORT_REFERENCE,04,03 */
    0x0a, 0x00, 0x02, 0x00, 0x49, 0x00, 0x08, 0x29, 0x04, 0x03,

    /* CHARACTERISTIC,  2a4b, READ | DYNAMIC, */
    // 0x004a CHARACTERISTIC 2a4b READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x4a, 0x00, 0x03, 0x28, 0x02, 0x4b, 0x00, 0x4b, 0x2a,
    // 0x004b VALUE 2a4b READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x4b, 0x00, 0x4b, 0x2a,

    /* CHARACTERISTIC,  2a33, READ | WRITE | NOTIFY, */
    // 0x004c CHARACTERISTIC 2a33 READ | WRITE | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x4c, 0x00, 0x03, 0x28, 0x1a, 0x4d, 0x00, 0x33, 0x2a,
    // 0x004d VALUE 2a33 READ | WRITE | NOTIFY
    0x08, 0x00, 0x1a, 0x00, 0x4d, 0x00, 0x33, 0x2a,
    // 0x004e CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x4e, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  2a4a, READ | DYNAMIC, */
    // 0x004f CHARACTERISTIC 2a4a READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x4f, 0x00, 0x03, 0x28, 0x02, 0x50, 0x00, 0x4a, 0x2a,
    // 0x0050 VALUE 2a4a READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x50, 0x00, 0x4a, 0x2a,

    /* CHARACTERISTIC,  2a4c, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0051 CHARACTERISTIC 2a4c WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x51, 0x00, 0x03, 0x28, 0x04, 0x52, 0x00, 0x4c, 0x2a,
    // 0x0052 VALUE 2a4c WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x52, 0x00, 0x4c, 0x2a,

    //////////////////////////////////////////////////////
    //
    // 0x0053 PRIMARY_SERVICE  ae40
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x53, 0x00, 0x00, 0x28, 0x40, 0xae,

    /* CHARACTERISTIC,  ae41, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0054 CHARACTERISTIC ae41 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x54, 0x00, 0x03, 0x28, 0x04, 0x55, 0x00, 0x41, 0xae,
    // 0x0055 VALUE ae41 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x55, 0x00, 0x41, 0xae,

    /* CHARACTERISTIC,  ae42, NOTIFY, */
    // 0x0056 CHARACTERISTIC ae42 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x56, 0x00, 0x03, 0x28, 0x10, 0x57, 0x00, 0x42, 0xae,
    // 0x0057 VALUE ae42 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x57, 0x00, 0x42, 0xae,
    // 0x0058 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x58, 0x00, 0x02, 0x29, 0x00, 0x00,
#endif
    // END
    0x00, 0x00,
};
//
// characteristics <--> handles
//
#define ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_2a01_01_VALUE_HANDLE 0x0005
#define ATT_CHARACTERISTIC_2a04_01_VALUE_HANDLE 0x0007
#define ATT_CHARACTERISTIC_2a05_01_VALUE_HANDLE 0x000a
#define ATT_CHARACTERISTIC_2a05_01_CLIENT_CONFIGURATION_HANDLE 0x000b
#define ATT_CHARACTERISTIC_af01_01_VALUE_HANDLE 0x000e
#define ATT_CHARACTERISTIC_af02_01_VALUE_HANDLE 0x0010
#define ATT_CHARACTERISTIC_af02_01_CLIENT_CONFIGURATION_HANDLE 0x0011
#define ATT_CHARACTERISTIC_af03_01_VALUE_HANDLE 0x0013
#define ATT_CHARACTERISTIC_af04_01_VALUE_HANDLE 0x0015
#define ATT_CHARACTERISTIC_af04_01_CLIENT_CONFIGURATION_HANDLE 0x0016
#define ATT_CHARACTERISTIC_af05_01_VALUE_HANDLE 0x0018
#define ATT_CHARACTERISTIC_af06_01_VALUE_HANDLE 0x001a
#define ATT_CHARACTERISTIC_af06_01_CLIENT_CONFIGURATION_HANDLE 0x001b
#define ATT_CHARACTERISTIC_af07_01_VALUE_HANDLE 0x001d
#define ATT_CHARACTERISTIC_af08_01_VALUE_HANDLE 0x001f
#define ATT_CHARACTERISTIC_af08_01_CLIENT_CONFIGURATION_HANDLE 0x0020
#define ATT_CHARACTERISTIC_2a29_01_VALUE_HANDLE 0x0023
#define ATT_CHARACTERISTIC_2a24_01_VALUE_HANDLE 0x0025
#define ATT_CHARACTERISTIC_2a25_01_VALUE_HANDLE 0x0027
#define ATT_CHARACTERISTIC_2a27_01_VALUE_HANDLE 0x0029
#define ATT_CHARACTERISTIC_2a26_01_VALUE_HANDLE 0x002b
#define ATT_CHARACTERISTIC_2a28_01_VALUE_HANDLE 0x002d
#define ATT_CHARACTERISTIC_2a23_01_VALUE_HANDLE 0x002f
#define ATT_CHARACTERISTIC_2a2a_01_VALUE_HANDLE 0x0031
#define ATT_CHARACTERISTIC_2a50_01_VALUE_HANDLE 0x0033
#define ATT_CHARACTERISTIC_2a19_01_VALUE_HANDLE 0x0036
#define ATT_CHARACTERISTIC_2a19_01_CLIENT_CONFIGURATION_HANDLE 0x0037
#define ATT_CHARACTERISTIC_2a4e_01_VALUE_HANDLE 0x003a
#define ATT_CHARACTERISTIC_2a4d_01_VALUE_HANDLE 0x003c
#define ATT_CHARACTERISTIC_2a4d_01_CLIENT_CONFIGURATION_HANDLE 0x003d
#define ATT_CHARACTERISTIC_2a4d_02_VALUE_HANDLE 0x0040
#define ATT_CHARACTERISTIC_2a4d_02_CLIENT_CONFIGURATION_HANDLE 0x0041
#define ATT_CHARACTERISTIC_2a4d_03_VALUE_HANDLE 0x0044
#define ATT_CHARACTERISTIC_2a4d_03_CLIENT_CONFIGURATION_HANDLE 0x0045
#define ATT_CHARACTERISTIC_2a4d_04_VALUE_HANDLE 0x0048
#define ATT_CHARACTERISTIC_2a4b_01_VALUE_HANDLE 0x004b
#define ATT_CHARACTERISTIC_2a33_01_VALUE_HANDLE 0x004d
#define ATT_CHARACTERISTIC_2a33_01_CLIENT_CONFIGURATION_HANDLE 0x004e
#define ATT_CHARACTERISTIC_2a4a_01_VALUE_HANDLE 0x0050
#define ATT_CHARACTERISTIC_2a4c_01_VALUE_HANDLE 0x0052
#define ATT_CHARACTERISTIC_ae41_01_VALUE_HANDLE 0x0055
#define ATT_CHARACTERISTIC_ae42_01_VALUE_HANDLE 0x0057
#define ATT_CHARACTERISTIC_ae42_01_CLIENT_CONFIGURATION_HANDLE 0x0058

//--------------------------------------------
#endif
