/* Bija Test is a Property Based Testing Framework for Bija specifically since I
   don't want to use a bloated testing framework to doing testing on some proeprties.

   Also I can learn how PBT works, how does RNG works and what makes it reproducible
   , etc., that I wouldn't have otherwise learned.

   This is only within a single header library because having a translation unit
   outside of the header is not needed for only a handful of functions / structs.
*/

#ifndef BIJA_TEST_H
#define BIJA_TEST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../bija.h"

/* ==== Random Number (XORSHIFT32), Random Vec, and Random Mat Generators ==== */
static inline uint32_t btest_xorshift32(uint32_t *state)
{
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x << 17;
    x ^= x << 5;
    return *state = x;
}

float btest_randfloat(uint32_t *state)
{
    uint32_t rand_num = btest_xorshift32(state);
    return (float)rand_num / UINT32_MAX; // Normalizes the rand_num to be in [0, 1]
}

static inline Vec2D_f btest_random_vec2df(uint32_t *state)
{
    return (Vec2D_f){
        .x = btest_randfloat(state),
        .y = btest_randfloat(state)};
}
static inline Vec3D_f btest_random_vec3df(uint32_t *state)
{
    return (Vec3D_f){
        .x = btest_randfloat(state),
        .y = btest_randfloat(state),
        .z = btest_randfloat(state)};
}
static inline Vec4D_f btest_random_vec4df(uint32_t *state)
{
    return (Vec4D_f){
        .x = btest_randfloat(state),
        .y = btest_randfloat(state),
        .z = btest_randfloat(state),
        .w = btest_randfloat(state),
    };
}

static inline Mat2_f btest_random_mat2f(uint32_t *state)
{
    return (Mat2_f){
        .elems = {btest_randfloat(state),
                  btest_randfloat(state),
                  btest_randfloat(state),
                  btest_randfloat(state)}};
}
static inline Mat3_f btest_random_mat3f(uint32_t *state)
{
    return (Mat3_f){
        .elems = {
            btest_randfloat(state), btest_randfloat(state), btest_randfloat(state),
            btest_randfloat(state), btest_randfloat(state), btest_randfloat(state),
            btest_randfloat(state), btest_randfloat(state), btest_randfloat(state)}};
}

/* ==== Property Based Test Runner ==== */
typedef bool (*PropertyFunc)(uint32_t *state);
typedef struct
{
    char *name;
    PropertyFunc func;
    size_t iterations;
} Btest_PropertyTest;

void btest_pbt_runner(uint32_t *state, Btest_PropertyTest *registry, size_t registry_cnt)
{
    size_t pbt_passed = 0;
    size_t pbt_failed = 0;
    for (size_t i = 0; i < registry_cnt; i++)
    {
        Btest_PropertyTest *property = &registry[i];

        for (size_t iter = 0; iter < property->iterations; iter++)
        {
            if (!property->func(state))
            {
                pbt_failed++;
                printf("PROPERTY FAILED\n");
                printf("-----------------------------\n");
                printf("Name      : %s\n", property->name);
                printf("Seed      : %ls\n", state);
                printf("Iteration : %zu\n", property->iterations);
                printf("-----------------------------\n");
                return;
            }
            pbt_passed++;
        }
    }

    printf("STATISTICS\n");
    printf("-------------------------------------\n");
    printf("PASSED : %zu\n", pbt_passed);
    printf("FAILED : %zu\n", pbt_failed);
    printf("-------------------------------------\n");
}
#endif // BIJA_TEST_H