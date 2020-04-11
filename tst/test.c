/**
 * @file
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "test.h"
#include "atto/atto.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

static void test_to_grey(void)
{
    atto_eq(0b0000, greyco64_to(0));
    atto_eq(0b0001, greyco64_to(1));
    atto_eq(0b0011, greyco64_to(2));
    atto_eq(0b0010, greyco64_to(3));
    atto_eq(0b0110, greyco64_to(4));
    atto_eq(0b0111, greyco64_to(5));
    atto_eq(0b0101, greyco64_to(6));
    atto_eq(0b0100, greyco64_to(7));
    atto_eq(0b1100, greyco64_to(8));
    atto_eq(0b1101, greyco64_to(9));
    atto_eq(0b1111, greyco64_to(10));
    atto_eq(0b1110, greyco64_to(11));
    atto_eq(0b1010, greyco64_to(12));
    atto_eq(0b1011, greyco64_to(13));
    atto_eq(0b1001, greyco64_to(14));
    atto_eq(0b1000, greyco64_to(15));
    atto_eq(0x8000000000000000ULL, greyco64_to(0xFFFFFFFFFFFFFFFFULL));
}

static void test_from_grey(void)
{
    atto_eq(0, greyco64_from(0b0000));
    atto_eq(1, greyco64_from(0b0001));
    atto_eq(2, greyco64_from(0b0011));
    atto_eq(3, greyco64_from(0b0010));
    atto_eq(4, greyco64_from(0b0110));
    atto_eq(5, greyco64_from(0b0111));
    atto_eq(6, greyco64_from(0b0101));
    atto_eq(7, greyco64_from(0b0100));
    atto_eq(8, greyco64_from(0b1100));
    atto_eq(9, greyco64_from(0b1101));
    atto_eq(10, greyco64_from(0b1111));
    atto_eq(11, greyco64_from(0b1110));
    atto_eq(12, greyco64_from(0b1010));
    atto_eq(13, greyco64_from(0b1011));
    atto_eq(14, greyco64_from(0b1001));
    atto_eq(15, greyco64_from(0b1000));
    atto_eq(0xFFFFFFFFFFFFFFFFULL, greyco64_from(0x8000000000000000ULL));
}

static void test_increment(void)
{
    atto_eq(greyco64_to(1), greyco64_incr(greyco64_to(0)));
    atto_eq(greyco64_to(2), greyco64_incr(greyco64_to(1)));
    atto_eq(greyco64_to(3), greyco64_incr(greyco64_to(2)));
    atto_eq(greyco64_to(4), greyco64_incr(greyco64_to(3)));
    atto_eq(greyco64_to(5), greyco64_incr(greyco64_to(4)));
    atto_eq(greyco64_to(6), greyco64_incr(greyco64_to(5)));
    atto_eq(greyco64_to(7), greyco64_incr(greyco64_to(6)));
    atto_eq(greyco64_to(8), greyco64_incr(greyco64_to(7)));
    atto_eq(greyco64_to(9), greyco64_incr(greyco64_to(8)));
    atto_eq(greyco64_to(10), greyco64_incr(greyco64_to(9)));
    atto_eq(greyco64_to(11), greyco64_incr(greyco64_to(10)));
    atto_eq(greyco64_to(12), greyco64_incr(greyco64_to(11)));
    atto_eq(greyco64_to(13), greyco64_incr(greyco64_to(12)));
    atto_eq(greyco64_to(14), greyco64_incr(greyco64_to(13)));
    atto_eq(greyco64_to(15), greyco64_incr(greyco64_to(14)));
    atto_eq(greyco64_to(16), greyco64_incr(greyco64_to(15)));
    atto_eq(0, greyco64_incr(greyco64_to(UINT64_MAX)));
}

static void test_decrement(void)
{
    atto_eq(greyco64_to(UINT64_MAX), greyco64_decr(greyco64_to(0)));
    atto_eq(greyco64_to(0), greyco64_decr(greyco64_to(1)));
    atto_eq(greyco64_to(1), greyco64_decr(greyco64_to(2)));
    atto_eq(greyco64_to(2), greyco64_decr(greyco64_to(3)));
    atto_eq(greyco64_to(3), greyco64_decr(greyco64_to(4)));
    atto_eq(greyco64_to(4), greyco64_decr(greyco64_to(5)));
    atto_eq(greyco64_to(5), greyco64_decr(greyco64_to(6)));
    atto_eq(greyco64_to(6), greyco64_decr(greyco64_to(7)));
    atto_eq(greyco64_to(7), greyco64_decr(greyco64_to(8)));
    atto_eq(greyco64_to(8), greyco64_decr(greyco64_to(9)));
    atto_eq(greyco64_to(9), greyco64_decr(greyco64_to(10)));
    atto_eq(greyco64_to(10), greyco64_decr(greyco64_to(11)));
    atto_eq(greyco64_to(11), greyco64_decr(greyco64_to(12)));
    atto_eq(greyco64_to(12), greyco64_decr(greyco64_to(13)));
    atto_eq(greyco64_to(13), greyco64_decr(greyco64_to(14)));
    atto_eq(greyco64_to(14), greyco64_decr(greyco64_to(15)));
    atto_eq(greyco64_to(UINT64_MAX - 1),
            greyco64_decr(greyco64_to(UINT64_MAX)));
}

#ifdef WIN32
// https://stackoverflow.com/questions/2349776/how-can-i-benchmark-c-code-easily
#include <windows.h>
static double current_time_micros(void)
{
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&time);
    QueryPerformanceFrequency(&frequency);
    return (double) time.QuadPart / (double) frequency.QuadPart;
}
#else
#include <sys/time.h>
#include <sys/resource.h>

static double current_time_micros(void)
{
    struct timeval time;
    struct timezone time_zone;
    gettimeofday(&time, &time_zone);
    return time.tv_sec + time.tv_usec * 1e-6;
}

#endif

static void test_benchmark(void)
{
    const uint64_t iterations = (uint64_t) 5e6;
    double start;
    double elapsed;
    double faster;
    uint64_t* results = malloc(iterations * sizeof(uint64_t));

    printf("Iterations: %"PRIu64"\n", iterations);
    start = current_time_micros();
    for (uint64_t i = 0; i < iterations; i++)
    {
        results[i] = greyco64_to(i);
    }
    elapsed = current_time_micros() - start;
    printf("Benchmark to-Grey.\tElapsed: %f s = %e/iteration\n",
           elapsed, elapsed / iterations);

    start = current_time_micros();
    for (uint64_t i = 0; i < iterations; i++)
    {
        results[i] = greyco64_from(i);
    }
    elapsed = current_time_micros() - start;
    printf("Benchmark from-Grey.\tElapsed: %f s = %e/iteration\n",
           elapsed, elapsed / iterations);

    start = current_time_micros();
    for (uint64_t i = 0; i < iterations; i++)
    {
        results[i] = greyco64_incr(i);
    }
    elapsed = current_time_micros() - start;
    printf("Benchmark incr-Grey.\tElapsed: %f s = %e/iteration\n",
           elapsed, elapsed / iterations);
    faster = elapsed;

    start = current_time_micros();
    for (uint64_t i = 0; i < iterations; i++)
    {
        uint64_t tmp = greyco64_from(i);
        tmp--;
        results[i] = greyco64_to(tmp);
    }
    elapsed = current_time_micros() - start;
    printf("Benchmark manual-incr.\tElapsed: %f s = %e/iteration\n",
           elapsed, elapsed / iterations);
    printf("Fast increment is %6.2f%% faster than manual increment\n",
           (1.0 - faster / elapsed) * 100);

    start = current_time_micros();
    for (uint64_t i = 0; i < iterations; i++)
    {
        results[i] = greyco64_decr(i);
    }
    elapsed = current_time_micros() - start;
    printf("Benchmark decr-Grey.\tElapsed: %f s = %e/iteration\n",
           elapsed, elapsed / iterations);
    faster = elapsed;

    start = current_time_micros();
    for (uint64_t i = 0; i < iterations; i++)
    {
        uint64_t tmp = greyco64_from(i);
        tmp++;
        results[i] = greyco64_to(tmp);
    }
    elapsed = current_time_micros() - start;
    printf("Benchmark manual-decr.\tElapsed: %f s = %e/iteration\n",
           elapsed, elapsed / iterations);
    printf("Fast decrement is %6.2f%% faster than manual decrement\n",
           (1.0 - faster / elapsed) * 100);
    free(results);
}


int main(void)
{
    test_to_grey();
    test_from_grey();
    test_increment();
    test_decrement();
    test_benchmark();
    return atto_at_least_one_fail;
}
