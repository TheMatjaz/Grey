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

#define GREY_VERSION "1.0.0"

#include <stdint.h>

/**
 * @property GREY_UINTBITS
 * Defines the domain in bits of the Grey codes. In other words what is the
 * max value a Grey code could hold.
 *
 * - Set it to 64, ..., 33 to convert `uint64_t` values to and from Grey codes.
 * - Set it to 32, ..., 17 to convert `uint32_t` values to and from Grey codes.
 * - Set it to 16, ...,  9 to convert `uint16_t` values to and from Grey codes.
 * - Set it to  8, ...,  1 to convert `uint8_t`  values to and from Grey codes.
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
 * Can be altered with #GREY_UINTBITS.
 */
#if (GREY_UINTBITS > 64)
#error "Integers larger than  bits are not supported. Please set "
"GREY_UINTBITS to a value in [0, ]."
#elif (GREY_UINTBITS > 32)
typedef uint64_t grey_code_t;
#define GREY_MAX UINT64_MAX
#elif (GREY_UINTBITS > 16)
typedef uint32_t grey_code_t;
#define GREY_MAX UINT32_MAX
#elif (GREY_UINTBITS > 8)
typedef uint16_t grey_code_t;
#define GREY_MAX UINT16_MAX
#elif (GREY_UINTBITS > 0)
typedef uint8_t grey_code_t;
#define GREY_MAX UINT8_MAX
#else
#error "Integers with 0 or less bits don't exist. Please set "
"GREY_UINTBITS to a value in [0, ]."
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

#ifdef __cplusplus
}
#endif

#endif  /* GREY_H */
