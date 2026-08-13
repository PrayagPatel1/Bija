#define BIJA_IMPLEMENTATION
#include "../bija_test.h"

static bool prop_add_commutative_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);

    return vec2df_equal(vec2df_add(a, b), vec2df_add(b, a));
}
static bool prop_add_associative_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);
    Vec2D_f c = btest_random_vec2df(state);
    return vec2df_equal(vec2df_add(vec2df_add(a, b), c), vec2df_add(a, vec2df_add(b, c)));
}
static bool prop_sub_is_add_negate_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);
    return vec2df_equal(vec2df_sub(a, b), vec2df_add(a, vec2df_negate(b)));
}
static bool prop_scale_distributes_over_vecadd_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);
    float k = btest_randfloat(state);
    return vec2df_equal(vec2df_scale(vec2df_add(a, b), k),
                        vec2df_add(vec2df_scale(a, k), vec2df_scale(b, k)));
}
static bool prop_scale_identity_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    return vec2df_equal(vec2df_scale(a, 1.0f), a);
}
static bool prop_triangle_inequality_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);
    return vec2df_mag(vec2df_add(a, b)) <= vec2df_mag(a) + vec2df_mag(b) + BIJA_EPSILON;
}
static bool prop_cross_anticommutative_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);
    return float_eq_approx(vec2df_cross(a, b), -vec2df_cross(b, a));
}
static bool prop_proj_idempotent_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f b = btest_random_vec2df(state);

    Vec2D_f p1 = vec2df_proj(a, b);
    Vec2D_f p2 = vec2df_proj(p1, b);
    return vec2df_equal(p1, p2);
}
static bool prop_floor_ceil_bound_v2(uint32_t *state)
{
    Vec2D_f a = btest_random_vec2df(state);
    Vec2D_f f = vec2df_floor(a);
    Vec2D_f c = vec2df_ceil(a);
    return f.x <= a.x + BIJA_EPSILON &&
           a.x <= c.x + BIJA_EPSILON &&
           f.y <= a.y + BIJA_EPSILON &&
           a.y <= c.y + BIJA_EPSILON;
}

int main(void)
{
    uint32_t state = 2463534242;
    Btest_PropertyTest registry[] = {
        (Btest_PropertyTest){
            .name = "Vec2D_f Add Commutativity",
            .func = &prop_add_commutative_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Add Associativity",
            .func = &prop_add_associative_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Sub and Add Negate",
            .func = &prop_sub_is_add_negate_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Scale Distribution Over Add",
            .func = &prop_scale_distributes_over_vecadd_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2d_f Scale Identity",
            .func = &prop_scale_identity_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Triangle Inequality",
            .func = &prop_triangle_inequality_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Cross Anticommutative",
            .func = &prop_cross_anticommutative_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Projection Idempotent",
            .func = &prop_proj_idempotent_v2,
            .iterations = 100},
        (Btest_PropertyTest){
            .name = "Vec2D_f Floor Ceil Bound",
            .func = &prop_floor_ceil_bound_v2,
            .iterations = 100}};

    btest_pbt_runner(&state, registry, sizeof(registry) / sizeof(registry[0]));
    return 0;
}