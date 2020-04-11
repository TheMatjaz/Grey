/**
 * @file
 * @brief
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "grey.h"

grey_code_t inline grey_to(const grey_int_t binary)
{
    return binary ^ (binary >> 1U);
}

grey_int_t grey_from(grey_code_t grey)
{
#if (GREY_UINTBITS > 32)
    grey ^= grey >> 32U;
#endif
#if (GREY_UINTBITS > 16)
    grey ^= grey >> 16U;
#endif
#if (GREY_UINTBITS > 8)
    grey ^= grey >> 8U;
#endif
    grey ^= grey >> 4U;
    grey ^= grey >> 2U;
    grey ^= grey >> 1U;
    return grey;
}

uint8_t grey_binstr(char* str, const grey_code_t grey)
{
    uint8_t len = 0;
    uint_fast8_t found_a_1 = 0;
    for (int_fast8_t i = GREY_UINTBITS - 1; i >= 0; i--)
    {
        const uint_fast8_t bit = (grey >> (unsigned int) i) & 1U;
        if (bit)
        {
            found_a_1 = i;
            str[len++] = '1';
        }
        else if (found_a_1)
        {
            str[len++] = '0';
        }
    }
    str[len] = '\0';
    return len;
}
