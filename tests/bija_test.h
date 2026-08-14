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
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../bija.h"

#define REGISTRY_CAP 100
#define REGISTRY_ITER 100

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

/* ==== PBT Registration ==== */
typedef bool (*PropertyFunc)(uint32_t *state);

typedef struct
{
    char *name;
    PropertyFunc func;
    size_t iterations;
} Btest_PropertyTest;

Btest_PropertyTest *registry = NULL; // Dynamically Allocated
size_t count = 0;
size_t capacity = 0;

static inline void btest_register_pbt(char *name, PropertyFunc func, size_t iterations)
{
    if (count >= capacity)
    {
        capacity = (capacity == 0) ? REGISTRY_CAP : REGISTRY_CAP * 2;
        Btest_PropertyTest *temp = realloc(registry, sizeof(Btest_PropertyTest) * capacity);
        if (temp == NULL)
        {
            perror("realloc has failed");
            exit(EXIT_FAILURE);
        }
        registry = temp;
    }

    registry[count].name = name;
    registry[count].func = func;
    registry[count].iterations = iterations;
    count++;
}

#if defined(__GNUC__) || defined(__clang__)
#define CONCAT_HIDDEN(x, y) x##y
#define CONCATE(x, y) CONCAT_HIDDEN(x, y)
#define BTEST_REGISTER(pbt_name, func)                                      \
    __attribute__((constructor)) void CONCATE(register_pbt, __LINE__)(void) \
    {                                                                       \
        btest_register_pbt((pbt_name), &(func), 100);                       \
    }
#else
#error "Could Not Do Automatic PBT Test Registration. Use btest_register_pbt() manually."
#endif

/* ==== PBT RUNNER ==== */
void btest_pbt_runner(uint32_t *state)
{
    size_t pbt_passed = 0;
    size_t pbt_failed = 0;
    for (size_t i = 0; i < count; i++)
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