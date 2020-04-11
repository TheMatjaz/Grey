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

#define greyco64_add(grey, delta) greyco64_to(greyco64_from((grey)) + (delta))
#define greyco64_incr(grey) greyco64_add((grey), 1)
#define greyco64_decr(grey) greyco64_add((grey), -1)

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

#ifdef __cplusplus
}
#endif

#endif  /* GREYCO_H */
