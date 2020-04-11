/**
 * @file
 * @brief
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "greyco.h"

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
