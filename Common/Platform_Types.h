#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#define CPU_TYPE_8              8
#define CPU_TYPE_16             16
#define CPU_TYPE_32             32
#define CPU_TYPE_64             64

#define CPU_TYPE                CPU_TYPE_32     /* Cortex-M4 is a 32-bit core */

#define LSB_FIRST                0     /* little endian bit ordering  */
#define MSB_FIRST                1     /* big endian bit ordering     */

#define CPU_BIT_ORDER            LSB_FIRST

#define LOW_BYTE_FIRST            0    /* little endian byte ordering */
#define HIGH_BYTE_FIRST           1    /* big endian byte ordering    */

#define CPU_BYTE_ORDER           LOW_BYTE_FIRST

typedef unsigned char           boolean;      /* TRUE .. FALSE */

#ifndef TRUE
#define TRUE                    1u
#endif

#ifndef FALSE
#define FALSE                   0u
#endif

typedef unsigned char           uint8;         /* 0 .. 255                */
typedef signed char             sint8;         /* -128 .. 127             */

typedef unsigned short          uint16;        /* 0 .. 65535              */
typedef signed short            sint16;        /* -32768 .. 32767         */

typedef unsigned long           uint32;        /* 0 .. 4294967295         */
typedef signed long             sint32;        /* -2147483648 .. 2147483647 */

typedef unsigned long long      uint64;        /* 0 .. 18446744073709551615 */
typedef signed long long        sint64;        /* -9223372036854775808 .. 9223372036854775807 */

typedef float                   float32;
typedef double                  float64;

typedef unsigned char            uint8_least;
typedef signed char              sint8_least;
typedef unsigned short           uint16_least;
typedef signed short             sint16_least;
typedef unsigned long            uint32_least;
typedef signed long              sint32_least;

#endif /* PLATFORM_TYPES_H */
