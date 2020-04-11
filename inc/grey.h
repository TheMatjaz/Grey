/**
 * @file
 * @brief
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#ifndef GREY_H
#define GREY_H

#ifdef __cplusplus
extern "C"
{
#endif

/** Version of the grey.h API using semantic versioning. */
#define GREY_VERSION "1.0.0"

#include <stdint.h>
#include <inttypes.h>

/**
 * @property GREY_UINTBITS
 * Defines the domain in bits of the Grey codes. In other words what is the
 * max value a Grey code could hold.
 *
 * - Set it to 64 to convert `uint64_t` values to and from Grey codes.
 * - Set it to 32 to convert `uint32_t` values to and from Grey codes.
 * - Set it to 16 to convert `uint16_t` values to and from Grey codes.
 * - Set it to  8 to convert `uint8_t`  values to and from Grey codes.
 *
 * #grey_code_t and #grey_int_t will automatically be defined as the proper
 * integer types to hold the Grey-encoded values and their binary (regular
 * integer) values.
 *
 * Defaults to 64 thus using `uint64_t` integers only, unless specified
 * otherwise at compile time,
 */
#ifndef GREY_UINTBITS
#define GREY_UINTBITS 64
#endif

/**
 * @property grey_code_t
 * Grey-encoded value, to distinguish them from binary values.
 *
 * Can be altered with #GREY_UINTBITS.
 */
/**
 * @property GREY_MAX
 * Maximum allowed value that #grey_code_t and #grey_int_t support.
 *
 * Can be increased with #GREY_UINTBITS.
 */
/**
 * @property GREY_FMT
 * Format specifier for `printf` and similar functions of the
 * decimal integer representation of #grey_code_t and #grey_int_t.
 *
 * Usage example:
 *
 *     grey_code_t code = 0x80U;
 *     printf("My Grey code is " GREY_FMT "!\n", code); // prints 128
 */
/**
 * @property GREY_FMTx
 * Format specifier for `printf` and similar functions of the
 * hexadecimal lowercase integer representation of #grey_code_t and
 * #grey_int_t.
 *
 * Usage example:
 *
 *     grey_code_t code = 0xF0U;
 *     printf("My Grey code is " GREY_FMTx "!\n", code); // prints "f0"
 */
/**
 * @property GREY_FMTX
 * Format specifier for `printf` and similar functions of the
 * hexadecimal uppercase integer representation of #grey_code_t and
 * #grey_int_t.
 *
 * Usage example:
 *
 *     grey_code_t code = 0xF0U;
 *     printf("My Grey code is " GREY_FMTX "!\n", code); // prints "F0"
 */
#if (GREY_UINTBITS == 64)
typedef uint64_t grey_code_t;
#define GREY_MAX ((uint64_t) UINT64_MAX)
#define GREY_FMT PRIu64
#define GREY_FMTx PRIx64
#define GREY_FMTX PRIX64
#elif (GREY_UINTBITS == 32)
typedef uint32_t grey_code_t;
#define GREY_MAX ((uint32_t) UINT32_MAX)
#define GREY_FMT PRIu32
#define GREY_FMTx PRIx32
#define GREY_FMTX PRIX32
#elif (GREY_UINTBITS == 16)
typedef uint16_t grey_code_t;
#define GREY_MAX ((uint16_t) UINT16_MAX)
#define GREY_FMT PRIu16
#define GREY_FMTx PRIx16
#define GREY_FMTX PRIX16
#elif (GREY_UINTBITS == 8)
typedef uint8_t grey_code_t;
#define GREY_MAX ((uint8_t) UINT8_MAX)
#define GREY_FMT PRIu8
#define GREY_FMTx PRIx8
#define GREY_FMTX PRIX8
#else
#error "Please set GREY_UINTBITS to a value in {8, 16, 32, 64}."
#endif

/** Binary value (regular integer), of the same size as Grey-coded values. */
typedef grey_code_t grey_int_t;

/**
 * Utility wrapper adding/subtracting a delta to a Grey-encoded value.
 *
 * @warning No checks are performed for overflows/underflows/integer conversion
 * errors etc.!
 * @param grey value to increase/decrease.
 * @param delta value to add/remove from the grey code, signed.
 * @return increased/decreased Grey code.
 */
#define grey_add(grey, delta) grey_to(grey_from((grey)) + (delta))

/**
 * Utility wrapper incrementing a Grey-encoded value by 1.
 *
 * @warning No checks are performed for overflows!
 * @param grey value to increment.
 * @return incremented Grey code = (grey+1).
 */
#define grey_incr(grey) grey_add((grey), 1)

/**
 * Utility wrapper decrementing a Grey-encoded value by 1.
 *
 * @warning No checks are performed for underflows!
 * @param grey value to decrement.
 * @return decremented Grey code = (grey-1).
 */
#define grey_decr(grey) grey_add((grey), -1)

/**
 * Converts a regular binary unsigned integer to Grey code.
 *
 * @param value the binary value (regular integer) to convert
 * @return \p value converted into Grey code
 */
grey_code_t grey_to(grey_int_t value);

/**
 * Converts a Grey-encoded value into a regular binary unsigned integer.
 *
 * @param grey value to convert
 * @return binary value (regular integer) of the Grey code
 */
grey_int_t grey_from(grey_code_t grey);


/**
 * Fills a string with the Grey code in binary representation.
 *
 * The representation is:
 * - ASCII
 * - big endian (as humans would read and write the number)
 * - contains no spaces
 * - is null-terminated
 * - is at most #GREY_UINTBITS bytes in size (EXCLUDING null-terminator).
 *
 * Example:
 *     `grey_binstr(str, 0x0E)` fills `str` with `"1110\0"` and returns `4`.
 *
 * Note: this is just a utility function, is not meant to be super-efficient.
 *
 * @param[out] str buffer of #GREY_UINTBITS+1 bytes (the "+1" is the space
 *             for the null-terminator.
 * @param[in] grey value to encode.
 * @returns length of the binary string written into \p str EXCLUDING the
 *          null-terminator
 */
uint8_t grey_binstr(char str[GREY_UINTBITS+1], grey_code_t grey);

#ifdef __cplusplus
}
#endif

#endif  /* GREY_H */
