#define BIJA_IMPLEMENTATION
#include "../bija_test.h"

static bool prop_add_commutative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return vec3df_equal(vec3df_add(a, b), vec3df_add(b, a));
}
static bool prop_add_associative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);
    Vec3D_f c = btest_random_vec3df(state);

    return vec3df_equal(vec3df_add(vec3df_add(a, b), c), vec3df_add(a, vec3df_add(b, c)));
}
static bool prop_sub_is_add_negate_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return vec3df_equal(vec3df_sub(a, b), vec3df_add(a, vec3df_negate(b)));
}
static bool prop_additive_inverse_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f zero = {.x = 0.0f,
                    .y = 0.0f,
                    .z = 0.0f};

    return vec3df_equal(vec3df_add(a, vec3df_negate(a)), zero);
}
static bool prop_scale_distributes_over_vecadd_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);
    float k = btest_randfloat(state);

    return vec3df_equal(vec3df_scale(vec3df_add(a, b), k),
                        vec3df_add(vec3df_scale(a, k), vec3df_scale(b, k)));
}
static bool prop_hadamard_commutative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return vec3df_equal(vec3df_hadamard_prod(a, b), vec3df_hadamard_prod(b, a));
}
static bool prop_hadamard_associative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);
    Vec3D_f c = btest_random_vec3df(state);

    return vec3df_equal(vec3df_hadamard_prod(vec3df_hadamard_prod(a, b), c),
                        vec3df_hadamard_prod(a, vec3df_hadamard_prod(b, c)));
}
static bool prop_hadamard_div_undoes_prod_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return vec3df_equal(vec3df_hadamard_div(vec3df_hadamard_prod(a, b), b), a);
}
static bool prop_dot_commutative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return float_eq_approx(vec3df_dot(a, b), vec3df_dot(b, a));
}
static bool prop_dot_distributes_over_add_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);
    Vec3D_f c = btest_random_vec3df(state);

    return float_eq_approx(vec3df_dot(a, vec3df_add(b, c)),
                           vec3df_dot(a, b) + vec3df_dot(a, c));
}
static bool prop_dot_scales_linearly_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);
    float k = btest_randfloat(state);

    return float_eq_approx(vec3df_dot(vec3df_scale(a, k), b), k * vec3df_dot(a, b));
}
static bool prop_dot_self_equals_mag_squared_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    float m = vec3df_mag(a);

    return float_eq_approx(vec3df_dot(a, a), m * m);
}
static bool prop_mag_absolute_homogeneity_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    float k = btest_randfloat(state);

    return float_eq_approx(vec3df_mag(vec3df_scale(a, k)), fabsf(k) * vec3df_mag(a));
}
static bool prop_scalaradd_distributes_over_scale_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    float k1 = btest_randfloat(state);
    float k2 = btest_randfloat(state);

    return vec3df_equal(vec3df_scale(a, k1 + k2),
                        vec3df_add(vec3df_scale(a, k1), vec3df_scale(a, k2)));
}
static bool prop_dist_symmetric_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return float_eq_approx(vec3df_dist(a, b), vec3df_dist(b, a));
}
static bool prop_dist_equals_mag_of_diff_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return float_eq_approx(vec3df_dist(a, b), vec3df_mag(vec3df_sub(a, b)));
}
static bool prop_dist_self_is_zero_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);

    return float_eq_approx(vec3df_dist(a, a), 0.0f);
}
static bool prop_cross_anticommutative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return vec3df_equal(vec3df_cross(a, b), vec3df_negate(vec3df_cross(b, a)));
}
static bool prop_cross_orthogonal_to_inputs_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);
    Vec3D_f c = vec3df_cross(a, b);

    return float_eq_approx(vec3df_dot(c, a), 0.0f) && float_eq_approx(vec3df_dot(c, b), 0.0f);
}
static bool prop_norm_produces_unit_vector_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);

    return float_eq_approx(vec3df_mag(vec3df_norm(a)), 1.0f);
}
static bool prop_norm_preserves_direction_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);

    return float_eq_approx(vec3df_dot(vec3df_norm(a), a), vec3df_mag(a));
}
static bool prop_min_max_commutative_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    return vec3df_equal(vec3df_min(a, b), vec3df_min(b, a)) && vec3df_equal(vec3df_max(a, b), vec3df_max(b, a));
}
static bool prop_min_le_max_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    Vec3D_f b = btest_random_vec3df(state);

    Vec3D_f lo = vec3df_min(a, b);
    Vec3D_f hi = vec3df_max(a, b);

    return lo.x <= hi.x + BIJA_EPSILON && lo.y <= hi.y + BIJA_EPSILON && lo.z <= hi.z + BIJA_EPSILON;
}
static bool prop_angle_self_is_zero_v3(uint32_t *state)
{
    Vec3D_f a = btest_random_vec3df(state);
    return float_eq_approx(vec3df_angle(a, a), 0.0f);
}

BTEST_REGISTER("Vec3D_f Addition Commutativity", prop_add_commutative_v3);
BTEST_REGISTER("Vec3D_f Addition Associativity", prop_add_associative_v3);
BTEST_REGISTER("Vec3D_f Subtraction is Addition Negate", prop_sub_is_add_negate_v3);
BTEST_REGISTER("Vec3D_f Additive Inverse", prop_additive_inverse_v3);
BTEST_REGISTER("Vec3D_f Scale Distributes Over Addition", prop_scale_distributes_over_vecadd_v3);
BTEST_REGISTER("Vec3D_f Hadamard Commutative", prop_hadamard_commutative_v3);
BTEST_REGISTER("Vec3D_f Hadamard Associative", prop_hadamard_associative_v3);
BTEST_REGISTER("Vec3D_f Hadamard Divison Undoes Product", prop_hadamard_div_undoes_prod_v3);
BTEST_REGISTER("Vec3D_f Dot Commutative", prop_dot_commutative_v3);
BTEST_REGISTER("Vec3D_f Dot Distributes Over Addition", prop_dot_distributes_over_add_v3);
BTEST_REGISTER("Vec3D_f Dot Scales Linearly", prop_dot_scales_linearly_v3);
BTEST_REGISTER("Vec3D_f Dot Self Equals Magnitude Squared", prop_dot_self_equals_mag_squared_v3);
BTEST_REGISTER("Vec3D_f Magnitude Absolute Homogeneity", prop_mag_absolute_homogeneity_v3);
BTEST_REGISTER("Vec3D_f Scalar Addition Distributes Over Scale", prop_scalaradd_distributes_over_scale_v3);
BTEST_REGISTER("Vec3D_f Distance Symmetric", prop_dist_symmetric_v3);
BTEST_REGISTER("Vec3D_f Distance Equals Magnitude of Difference", prop_dist_equals_mag_of_diff_v3);
BTEST_REGISTER("Vec3D_f Distance is Zero", prop_dist_self_is_zero_v3);
BTEST_REGISTER("Vec3D_f Cross Anticommutative", prop_cross_anticommutative_v3);
BTEST_REGISTER("Vec3D_f Cross Orthogonal to Inputs", prop_cross_orthogonal_to_inputs_v3);
BTEST_REGISTER("Vec3D_f Normal Produces Unit Vector", prop_norm_produces_unit_vector_v3);
BTEST_REGISTER("Vec3D_f Normal Perserves Direction", prop_norm_preserves_direction_v3);
BTEST_REGISTER("Vec3D_f Min Mac Commutative", prop_min_max_commutative_v3);
BTEST_REGISTER("Vec3D_f Min Less Than Max", prop_min_le_max_v3);
BTEST_REGISTER("Vec3D_f Angle is Zero", prop_angle_self_is_zero_v3);

// int main(void)
// {
// uint32_t state = 2463538692;
// btest_pbt_runner(&state);
// return 0;
// }