#define BIJA_IMPLEMENTATION
#include "../bija_test.h"

static bool prop_add_commutative_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);
    Vec4D_f b = btest_random_vec4df(state);

    return vec4df_equal(vec4df_add(a, b), vec4df_add(b, a));
}
static bool prop_add_associative_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);
    Vec4D_f b = btest_random_vec4df(state);
    Vec4D_f c = btest_random_vec4df(state);

    return vec4df_equal(vec4df_add(vec4df_add(a, b), c), vec4df_add(a, vec4df_add(b, c)));
}
static bool prop_sub_is_add_negate_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);
    Vec4D_f b = btest_random_vec4df(state);

    return vec4df_equal(vec4df_sub(a, b), vec4df_add(a, vec4df_negate(b)));
}
static bool prop_negate_involution_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);

    return vec4df_equal(vec4df_negate(vec4df_negate(a)), a);
}
static bool prop_scale_associative_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);
    float k1 = btest_randfloat(state);
    float k2 = btest_randfloat(state);

    return vec4df_equal(vec4df_scale(vec4df_scale(a, k2), k1),
                        vec4df_scale(a, k1 * k2));
}
static bool prop_mag_nonnegative_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);

    return vec4df_mag(a) >= 0.0f;
}
static bool prop_equal_reflexive_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);
    return vec4df_equal(a, a) != 0;
}
static bool prop_equal_symmetric_v4(uint32_t *state)
{
    Vec4D_f a = btest_random_vec4df(state);
    Vec4D_f b = btest_random_vec4df(state);

    return (vec4df_equal(a, b) != 0) == (vec4df_equal(b, a) != 0);
}

BTEST_REGISTER("Vec4D_f Addition Commutativity", prop_add_commutative_v4);
BTEST_REGISTER("Vec4D_f Addition Associativity", prop_add_associative_v4);
BTEST_REGISTER("Vec4D_f Subtraction Is Addition Negate", prop_sub_is_add_negate_v4);
BTEST_REGISTER("Vec4D_f Negate Involution", prop_negate_involution_v4);
BTEST_REGISTER("Vec4D_f Scale Associativity", prop_scale_associative_v4);
BTEST_REGISTER("Vec4D_f Magnitude Non-negative", prop_mag_nonnegative_v4);
BTEST_REGISTER("Vec4D_f Equal_reflexive", prop_equal_reflexive_v4);
BTEST_REGISTER("Vec4D_f Equal Symmetric", prop_equal_symmetric_v4);
