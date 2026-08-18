#define BIJA_IMPLEMENTATION
#include "../bija_test.h"

static bool prop_identity_is_mul_identity(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Mat2_f id = mat2df_get_identity();

    Mat2_f left = mat2df_mul(id, a);
    Mat2_f right = mat2df_mul(a, id);

    return mat2df_equal(left, a) && mat2df_equal(right, a);
}

static bool prop_det_identity_is_one(uint32_t *state)
{
    (void)state;
    Mat2_f id = mat2df_get_identity();
    return float_eq_approx(mat2df_det(id), 1.0f);
}

static bool prop_add_commutative(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Mat2_f b = btest_random_mat2f(state);
    return mat2df_equal(mat2df_add(a, b), mat2df_add(b, a));
}

static bool prop_add_associative(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state), c = btest_random_mat2f(state);
    Mat2_f lhs = mat2df_add(mat2df_add(a, b), c);
    Mat2_f rhs = mat2df_add(a, mat2df_add(b, c));
    return mat2df_equal(lhs, rhs);
}

static bool prop_sub_self_is_zero(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Mat2_f zero = mat2df_scale(a, 0.0f);
    return mat2df_equal(mat2df_sub(a, a), zero);
}

static bool prop_sub_equals_add_negation(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state);
    Mat2_f lhs = mat2df_sub(a, b);
    Mat2_f rhs = mat2df_add(a, mat2df_scale(b, -1.0f));
    return mat2df_equal(lhs, rhs);
}

static bool prop_scale_by_one_is_identity(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    return mat2df_equal(mat2df_scale(a, 1.0f), a);
}

static bool prop_scale_associative(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    float s = btest_randfloat(state);
    float t = btest_randfloat(state);
    Mat2_f lhs = mat2df_scale(mat2df_scale(a, s), t);
    Mat2_f rhs = mat2df_scale(a, s * t);
    return mat2df_equal(lhs, rhs);
}

static bool prop_scale_distributes_over_add(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state);
    float s = btest_randfloat(state);
    Mat2_f lhs = mat2df_scale(mat2df_add(a, b), s);
    Mat2_f rhs = mat2df_add(mat2df_scale(a, s), mat2df_scale(b, s));
    return mat2df_equal(lhs, rhs);
}

static bool prop_transpose_is_involution(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    return mat2df_equal(mat2df_transpose(mat2df_transpose(a)), a);
}

static bool prop_transpose_distributes_over_add(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state);
    Mat2_f lhs = mat2df_transpose(mat2df_add(a, b));
    Mat2_f rhs = mat2df_add(mat2df_transpose(a), mat2df_transpose(b));
    return mat2df_equal(lhs, rhs);
}

static bool prop_transpose_reverses_mul(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state);
    Mat2_f lhs = mat2df_transpose(mat2df_mul(a, b));
    Mat2_f rhs = mat2df_mul(mat2df_transpose(b), mat2df_transpose(a));
    return mat2df_equal(lhs, rhs);
}

static bool prop_det_invariant_under_transpose(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    return float_eq_approx(mat2df_det(mat2df_transpose(a)), mat2df_det(a));
}

static bool prop_mul_associative(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state), c = btest_random_mat2f(state);
    Mat2_f lhs = mat2df_mul(mat2df_mul(a, b), c);
    Mat2_f rhs = mat2df_mul(a, mat2df_mul(b, c));
    return mat2df_equal(lhs, rhs);
}

static bool prop_mul_distributes_over_add(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state), c = btest_random_mat2f(state);
    Mat2_f lhs = mat2df_mul(a, mat2df_add(b, c));
    Mat2_f rhs = mat2df_add(mat2df_mul(a, b), mat2df_mul(a, c));
    return mat2df_equal(lhs, rhs);
}

static bool prop_det_is_multiplicative(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state);
    float lhs = mat2df_det(mat2df_mul(a, b));
    float rhs = mat2df_det(a) * mat2df_det(b);
    return float_eq_approx(lhs, rhs);
}

static bool prop_vec_mul_identity(uint32_t *state)
{
    Vec2D_f v = btest_random_vec2df(state);
    Mat2_f id = mat2df_get_identity();

    return vec2df_equal(mat2df_vec_mul(id, v), v);
}

static bool prop_vec_mul_additive(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Vec2D_f v1 = btest_random_vec2df(state), v2 = btest_random_vec2df(state);
    Vec2D_f lhs = mat2df_vec_mul(a, vec2df_add(v1, v2));
    Vec2D_f rhs = vec2df_add(mat2df_vec_mul(a, v1), mat2df_vec_mul(a, v2));
    return vec2df_equal(lhs, rhs);
}

static bool prop_vec_mul_homogeneous(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Vec2D_f v = btest_random_vec2df(state);
    float s = btest_randfloat(state);
    Vec2D_f lhs = mat2df_vec_mul(a, vec2df_scale(v, s));
    Vec2D_f rhs = vec2df_scale(mat2df_vec_mul(a, v), s);
    return vec2df_equal(lhs, rhs);
}

static bool prop_vec_mul_matches_mat_composition(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state), b = btest_random_mat2f(state);
    Vec2D_f v = btest_random_vec2df(state);
    Vec2D_f lhs = mat2df_vec_mul(mat2df_mul(a, b), v);
    Vec2D_f rhs = mat2df_vec_mul(a, mat2df_vec_mul(b, v));
    return vec2df_equal(lhs, rhs);
}

static bool prop_equal_reflexive(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    return mat2df_equal(a, a) != 0;
}

static bool prop_equal_symmetric(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Mat2_f b = (btest_randfloat(state) < 0.5f) ? a : btest_random_mat2f(state); /* mix equal/unequal cases */
    return (mat2df_equal(a, b) != 0) == (mat2df_equal(b, a) != 0);
}

static bool prop_inverse_is_mul_inverse(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Mat2_f inv = mat2df_inverse(a);

    Mat2_f id = mat2df_get_identity();

    Mat2_f left = mat2df_mul(a, inv);
    Mat2_f right = mat2df_mul(inv, a);

    return mat2df_equal(left, id) && mat2df_equal(right, id);
}

static bool prop_inverse_is_involution(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    Mat2_f a2 = mat2df_inverse(mat2df_inverse(a));
    return mat2df_equal(a2, a);
}

static bool prop_inverse_det_is_reciprocal(uint32_t *state)
{
    Mat2_f a = btest_random_mat2f(state);
    float det_a = mat2df_det(a);
    float det_inv = mat2df_det(mat2df_inverse(a));

    return float_eq_rel(det_inv, 1.0f / det_a);
}

static bool prop_rotation_det_is_one(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Mat2_f r = mat2df_get_rotation(theta);
    return float_eq_approx(mat2df_det(r), 1.0f);
}

static bool prop_rotation_is_orthogonal(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Mat2_f r = mat2df_get_rotation(theta);
    Mat2_f rt = mat2df_transpose(r);
    Mat2_f id = mat2df_get_identity();
    return mat2df_equal(mat2df_mul(r, rt), id);
}

static bool prop_rotation_composition_adds_angles(uint32_t *state)
{
    float a = btest_randfloat(state);
    float b = btest_randfloat(state);
    Mat2_f ra = mat2df_get_rotation(a);
    Mat2_f rb = mat2df_get_rotation(b);
    Mat2_f combined = mat2df_mul(ra, rb);
    Mat2_f expected = mat2df_get_rotation(a + b);
    return mat2df_equal(combined, expected);
}

static bool prop_rotation_zero_is_identity(uint32_t *state)
{
    (void)state;
    Mat2_f r = mat2df_get_rotation(0.0f);
    Mat2_f id = mat2df_get_identity();
    return mat2df_equal(r, id);
}

static bool prop_rotation_preserves_length(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Vec2D_f v = btest_random_vec2df(state);
    Mat2_f r = mat2df_get_rotation(theta);
    Vec2D_f rv = mat2df_vec_mul(r, v);
    float len_before = sqrtf(v.x * v.x + v.y * v.y);
    float len_after = sqrtf(rv.x * rv.x + rv.y * rv.y);
    return float_eq_approx(len_before, len_after);
}

static bool prop_scaling_det_matches_factors(uint32_t *state)
{
    float sx = btest_randfloat(state);
    float sy = btest_randfloat(state);
    Mat2_f s = mat2df_get_scaling(sx, sy);
    return float_eq_approx(mat2df_det(s), sx * sy);
}

static bool prop_scaling_composition_multiplies_factors(uint32_t *state)
{
    float sx1 = btest_randfloat(state), sy1 = btest_randfloat(state);
    float sx2 = btest_randfloat(state), sy2 = btest_randfloat(state);
    Mat2_f s1 = mat2df_get_scaling(sx1, sy1);
    Mat2_f s2 = mat2df_get_scaling(sx2, sy2);
    Mat2_f combined = mat2df_mul(s1, s2);
    Mat2_f expected = mat2df_get_scaling(sx1 * sx2, sy1 * sy2);
    return mat2df_equal(combined, expected);
}

static bool prop_scaling_one_one_is_identity(uint32_t *state)
{
    (void)state;
    Mat2_f s = mat2df_get_scaling(1.0f, 1.0f);
    Mat2_f id = mat2df_get_identity();
    return mat2df_equal(s, id);
}

static bool prop_reflec_x_is_involution(uint32_t *state)
{
    (void)state;
    Mat2_f rx = mat2df_get_reflec_x();
    Mat2_f id = mat2df_get_identity();
    return mat2df_equal(mat2df_mul(rx, rx), id);
}

static bool prop_reflec_y_is_involution(uint32_t *state)
{
    (void)state;
    Mat2_f ry = mat2df_get_reflec_y();
    Mat2_f id = mat2df_get_identity();
    return mat2df_equal(mat2df_mul(ry, ry), id);
}

static bool prop_reflec_det_is_negative_one(uint32_t *state)
{
    (void)state;
    Mat2_f rx = mat2df_get_reflec_x();
    Mat2_f ry = mat2df_get_reflec_y();
    return float_eq_approx(mat2df_det(rx), -1.0f) &&
           float_eq_approx(mat2df_det(ry), -1.0f);
}

static bool prop_reflec_x_preserves_length(uint32_t *state)
{
    Vec2D_f v = btest_random_vec2df(state);
    Mat2_f rx = mat2df_get_reflec_x();
    Vec2D_f rv = mat2df_vec_mul(rx, v);
    float len_before = sqrtf(v.x * v.x + v.y * v.y);
    float len_after = sqrtf(rv.x * rv.x + rv.y * rv.y);
    return float_eq_approx(len_before, len_after);
}

static bool prop_shear_det_is_one(uint32_t *state)
{
    float x = btest_randfloat(state);
    float y = btest_randfloat(state);
    Mat2_f sh = mat2df_get_shear(x, y);

    return float_eq_rel(mat2df_det(sh), 1.0f);
}

static bool prop_shear_zero_is_identity(uint32_t *state)
{
    (void)state;
    Mat2_f sh = mat2df_get_shear(0.0f, 0.0f);
    Mat2_f id = mat2df_get_identity();
    return mat2df_equal(sh, id);
}

BTEST_REGISTER("Mat2D_f Identity is Mul Identity", prop_identity_is_mul_identity);
BTEST_REGISTER("Mat2D_f Determinant of Identity is One", prop_det_identity_is_one);

BTEST_REGISTER("Mat2D_f Addition Commutatively", prop_add_commutative);
BTEST_REGISTER("Mat2D_f Addition Associativity", prop_add_associative);
BTEST_REGISTER("Mat2D_f Subtraction Self is Zero", prop_sub_self_is_zero);
BTEST_REGISTER("Mat2D_f Subtraction Equals Add Negation", prop_sub_equals_add_negation);

BTEST_REGISTER("Mat2D_f Scale by One is Identity", prop_scale_by_one_is_identity);
BTEST_REGISTER("Mat2D_f Scale Associativity", prop_scale_associative);
BTEST_REGISTER("Mat2D_f Scale distributes Over Addition", prop_scale_distributes_over_add);
BTEST_REGISTER("Mat2D_f Transpose is Involution", prop_transpose_is_involution);
BTEST_REGISTER("Mat2D_f Transpose Distributes Over Addition", prop_transpose_distributes_over_add);
BTEST_REGISTER("Mat2D_f Transpose Reverses Multiplication", prop_transpose_reverses_mul);
BTEST_REGISTER("Mat2D_f Determinant Invariant Under Transpose", prop_det_invariant_under_transpose);

BTEST_REGISTER("Mat2D_f Multiplication Associativity", prop_mul_associative);
BTEST_REGISTER("Mat2D_f Multiplication Distributes Over Addition", prop_mul_distributes_over_add);
BTEST_REGISTER("Mat2D_f Determinant is Multiplicative", prop_det_is_multiplicative);

BTEST_REGISTER("Mat2D_f Vector Multiplication Identity", prop_vec_mul_identity);
BTEST_REGISTER("Mat2D_f Vector Multiplication Additive", prop_vec_mul_additive);
BTEST_REGISTER("Mat2D_f Vector Multiplication Homogeneous", prop_vec_mul_homogeneous);
BTEST_REGISTER("Mat2D_f Vector Multiplication Matches Matrix Composition", prop_vec_mul_matches_mat_composition);

BTEST_REGISTER("Mat2D_f Equal Reflexive", prop_equal_reflexive);
BTEST_REGISTER("Mat2D_f Equal Symmetric", prop_equal_symmetric);

BTEST_REGISTER("Mat2D_f Inverse is Multiplicative Inverse", prop_inverse_is_mul_inverse);
BTEST_REGISTER("Mat2D_f Inverse is Involution", prop_inverse_is_involution);
BTEST_REGISTER("Mat2D_f Inverse is Reciprocal", prop_inverse_det_is_reciprocal);

BTEST_REGISTER("Mat2D_f Rotation Determinant is One", prop_rotation_det_is_one);
BTEST_REGISTER("Mat2D_f Rotation is Orthogonal ", prop_rotation_is_orthogonal);
BTEST_REGISTER("Mat2D_f Rotation Composition Adds Angles", prop_rotation_composition_adds_angles);
BTEST_REGISTER("Mat2D_f Rotation Zero is Identity", prop_rotation_zero_is_identity);
BTEST_REGISTER("Mat2D_f Rotation Perserves Length", prop_rotation_preserves_length);

BTEST_REGISTER("Mat2D_f Scaling Determinant Matches Factors", prop_scaling_det_matches_factors);
BTEST_REGISTER("Mat2D_f Scaling Composition Multiplies Factors", prop_scaling_composition_multiplies_factors);
BTEST_REGISTER("Mat2D_f Scaling One is Identity", prop_scaling_one_one_is_identity);

BTEST_REGISTER("Mat2D_f Reflection X is Involution", prop_reflec_x_is_involution);
BTEST_REGISTER("Mat2D_f Reflection Y is involution", prop_reflec_y_is_involution);
BTEST_REGISTER("Mat2D_f Reflection Determinant is Negative One", prop_reflec_det_is_negative_one);
BTEST_REGISTER("Mat2D_f Reflection X Perserves Length", prop_reflec_x_preserves_length);

BTEST_REGISTER("Mat2D_f Shear Determinant is One", prop_shear_det_is_one);
BTEST_REGISTER("Mat2D_f Shear Zero is Identity", prop_shear_zero_is_identity);
