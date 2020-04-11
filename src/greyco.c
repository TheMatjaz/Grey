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
