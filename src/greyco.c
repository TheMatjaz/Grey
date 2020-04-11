/**
 * @file
 * @brief
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */
#include "../inc/greyco.h"

#define INCREMENT 1U
#define DECREMENT 0U

grey64_t inline greyco64_to(const uint64_t binary)
{
    return binary ^ (binary >> 1U);
}

uint64_t greyco64_from(grey64_t grey)
{
    grey ^= grey >> 32U;
    grey ^= grey >> 16U;
    grey ^= grey >> 8U;
    grey ^= grey >> 4U;
    grey ^= grey >> 2U;
    grey ^= grey >> 1U;
    return grey;
}

/**
 * Fast bit odd-parity check.
 *
 * @param x an integer
 * @return true if \p x contains an odd number of bits set to 1.
 */
static inline unsigned int is_number_of_bits_set_to_1_odd(uint64_t x)
{
    // From the amazing "Bit Twiddling Hacks" page
    // https://graphics.stanford.edu/~seander/bithacks.html##ParityMultiply
    // Note: yes, the link has a double #-sign, as the page contains a typo
    x ^= x >> 1U;
    x ^= x >> 2U;
    x = (x & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (x >> 60U) & 1U;
}

/**
 * Fast incrementing or decrementing of a grey code by 1 without converting
 * it to binary and back to grey code.
 *
 * @param grey code to increment or decrement
 * @param is_increment true (#INCREMENT) when the code must be increased by 1.
 *        False (#DECREMENT) when decreased by 1.
 * @return incremented/decremented grey code by 1
 */
static inline grey64_t greyco64_step(const uint64_t grey,
                                     const unsigned int is_increment)
{
    // Incrementing and decrementing uses the exact same operations,
    // just taking the opposite if-else branch.
    if (is_number_of_bits_set_to_1_odd(grey) ^ (!is_increment))
    {
        // Entered when incrementing a value with odd  amount of bits set to 1
        // or           decrementing a value with even amount of bits set to 1
        const uint64_t rightmost_1_bit = grey & (-grey);
        return grey ^ (rightmost_1_bit << 1U);
    }
    else
    {
        // Entered when incrementing a value with even amount of bits set to 1
        // or           decrementing a value with odd  amount of bits set to 1
        return grey ^ 1U;
    }
}

grey64_t greyco64_incr(const grey64_t grey)
{
    return greyco64_step(grey, INCREMENT);
}

grey64_t greyco64_decr(const grey64_t grey)
{
    return greyco64_step(grey, DECREMENT);
}
