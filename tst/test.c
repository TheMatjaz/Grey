/**
 * @file
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "test.h"
#include "atto.h"
#include <stdio.h>
#include <inttypes.h>

static void test_to_grey(void)
{
    atto_eq(0b0000, grey_to(0));
    atto_eq(0b0001, grey_to(1));
    atto_eq(0b0011, grey_to(2));
    atto_eq(0b0010, grey_to(3));
    atto_eq(0b0110, grey_to(4));
    atto_eq(0b0111, grey_to(5));
    atto_eq(0b0101, grey_to(6));
    atto_eq(0b0100, grey_to(7));
    atto_eq(0b1100, grey_to(8));
    atto_eq(0b1101, grey_to(9));
    atto_eq(0b1111, grey_to(10));
    atto_eq(0b1110, grey_to(11));
    atto_eq(0b1010, grey_to(12));
    atto_eq(0b1011, grey_to(13));
    atto_eq(0b1001, grey_to(14));
    atto_eq(0b1000, grey_to(15));
    atto_eq(0x80, grey_to(255));
}

static void test_from_grey(void)
{
    atto_eq(0, grey_from(0b0000));
    atto_eq(1, grey_from(0b0001));
    atto_eq(2, grey_from(0b0011));
    atto_eq(3, grey_from(0b0010));
    atto_eq(4, grey_from(0b0110));
    atto_eq(5, grey_from(0b0111));
    atto_eq(6, grey_from(0b0101));
    atto_eq(7, grey_from(0b0100));
    atto_eq(8, grey_from(0b1100));
    atto_eq(9, grey_from(0b1101));
    atto_eq(10, grey_from(0b1111));
    atto_eq(11, grey_from(0b1110));
    atto_eq(12, grey_from(0b1010));
    atto_eq(13, grey_from(0b1011));
    atto_eq(14, grey_from(0b1001));
    atto_eq(15, grey_from(0b1000));
    atto_eq(255, grey_from(0x80));
}

static void test_increment(void)
{
    atto_eq(grey_to(1), grey_incr(grey_to(0)));
    atto_eq(grey_to(2), grey_incr(grey_to(1)));
    atto_eq(grey_to(3), grey_incr(grey_to(2)));
    atto_eq(grey_to(4), grey_incr(grey_to(3)));
    atto_eq(grey_to(5), grey_incr(grey_to(4)));
    atto_eq(grey_to(6), grey_incr(grey_to(5)));
    atto_eq(grey_to(7), grey_incr(grey_to(6)));
    atto_eq(grey_to(8), grey_incr(grey_to(7)));
    atto_eq(grey_to(9), grey_incr(grey_to(8)));
    atto_eq(grey_to(10), grey_incr(grey_to(9)));
    atto_eq(grey_to(11), grey_incr(grey_to(10)));
    atto_eq(grey_to(12), grey_incr(grey_to(11)));
    atto_eq(grey_to(13), grey_incr(grey_to(12)));
    atto_eq(grey_to(14), grey_incr(grey_to(13)));
    atto_eq(grey_to(15), grey_incr(grey_to(14)));
    atto_eq(grey_to(16), grey_incr(grey_to(15)));
    atto_eq(grey_to(GREY_MAX), grey_incr(grey_to(GREY_MAX - 1)));
    atto_eq(0, grey_incr(grey_to(GREY_MAX)));
}

static void test_decrement(void)
{
    atto_eq(grey_to(GREY_MAX), grey_decr(grey_to(0)));
    atto_eq(grey_to(0), grey_decr(grey_to(1)));
    atto_eq(grey_to(1), grey_decr(grey_to(2)));
    atto_eq(grey_to(2), grey_decr(grey_to(3)));
    atto_eq(grey_to(3), grey_decr(grey_to(4)));
    atto_eq(grey_to(4), grey_decr(grey_to(5)));
    atto_eq(grey_to(5), grey_decr(grey_to(6)));
    atto_eq(grey_to(6), grey_decr(grey_to(7)));
    atto_eq(grey_to(7), grey_decr(grey_to(8)));
    atto_eq(grey_to(8), grey_decr(grey_to(9)));
    atto_eq(grey_to(9), grey_decr(grey_to(10)));
    atto_eq(grey_to(10), grey_decr(grey_to(11)));
    atto_eq(grey_to(11), grey_decr(grey_to(12)));
    atto_eq(grey_to(12), grey_decr(grey_to(13)));
    atto_eq(grey_to(13), grey_decr(grey_to(14)));
    atto_eq(grey_to(14), grey_decr(grey_to(15)));
    atto_eq(grey_to(GREY_MAX - 1),
            grey_decr(grey_to(GREY_MAX)));
}

int main(void)
{
    test_to_grey();
    test_from_grey();
    test_increment();
    test_decrement();
    return atto_at_least_one_fail;
}
