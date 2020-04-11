/**
 * @file
 * @brief
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#ifndef GREYCO_H
#define GREYCO_H

#ifdef __cplusplus
extern "C"
{
#endif

#define GREYCO_VERSION "1.0.0"

#include <stdint.h>

/** Grey-encoded value, to distinguish them from binary values. */
typedef uint64_t grey64_t;

/**
 * Converts a regular binary unsigned integer to Grey code.
 *
 * @param value the value to convert
 * @return \p value converted into Grey code
 */
grey64_t greyco64_to(uint64_t value);

/**
 * Converts a Grey-encoded value into a regular binary unsigned integer.
 *
 * @param grey value to convert
 * @return binary value of the Grey code
 */
uint64_t greyco64_from(grey64_t grey);

/**
 * Fast incrementing of a Grey code by 1 (`grey++`).
 *
 * It is approximately 2x faster than converting it to binary, incrementing it
 * and converting it again to Grey code.
 *
 * @warning It does NOT overflow! Incrementing a #UINT64_MAX returns a
 * #UINT64_MAX.
 *
 * @param grey Grey-encoded value to increment
 * @return \p grey + 1
 */
grey64_t greyco64_incr(grey64_t grey);

/**
 * Fast decrementing of a Grey code by 1 (`grey--`).
 *
 * It is approximately 2x faster than converting it to binary, decrementing it
 * and converting it again to Grey code.
 *
 * @warning It does NOT underflow! Decrementing a 0 returns a 0.
 *
 * @param grey Grey-encoded value to decrement
 * @return \p grey - 1
 */
grey64_t greyco64_decr(grey64_t grey);

#ifdef __cplusplus
}
#endif

#endif  /* GREYCO_H */
