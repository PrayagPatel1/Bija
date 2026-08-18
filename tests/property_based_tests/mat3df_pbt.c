#define BIJA_IMPLEMENTATION
#include "../bija_test.h"

static bool prop_identity_is_mul_identity(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f id = mat3df_get_identity();

    return mat3df_equal(mat3df_mul(id, a), a) &&
           mat3df_equal(mat3df_mul(a, id), a);
}

static bool prop_add_commutative(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f b = btest_random_mat3f(state);

    return mat3df_equal(mat3df_add(a, b), mat3df_add(b, a));
}

static bool prop_sub_self_is_zero(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f zero = mat3df_scale(a, 0.0f);

    return mat3df_equal(mat3df_sub(a, a), zero);
}

static bool prop_scale_distributes_over_add(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f b = btest_random_mat3f(state);

    float s = btest_randfloat(state);

    Mat3_f lhs = mat3df_scale(mat3df_add(a, b), s);
    Mat3_f rhs = mat3df_add(mat3df_scale(a, s), mat3df_scale(b, s));

    return mat3df_equal(lhs, rhs);
}

static bool prop_transpose_is_involution(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);

    return mat3df_equal(mat3df_transpose(mat3df_transpose(a)), a);
}

static bool prop_mul_associative(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f b = btest_random_mat3f(state);
    Mat3_f c = btest_random_mat3f(state);

    Mat3_f lhs = mat3df_mul(mat3df_mul(a, b), c);
    Mat3_f rhs = mat3df_mul(a, mat3df_mul(b, c));

    return mat3df_equal(lhs, rhs);
}

static bool prop_det_is_multiplicative(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f b = btest_random_mat3f(state);

    return float_eq_approx(mat3df_det(mat3df_mul(a, b)), mat3df_det(a) * mat3df_det(b));
}

static bool prop_vec_mul_identity(uint32_t *state)
{
    Vec3D_f v = btest_random_vec3df(state);
    Mat3_f id = mat3df_get_identity();

    return vec3df_equal(mat3df_vec_mul(id, v), v);
}

static bool prop_vec_mul_matches_mat_composition(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);
    Mat3_f b = btest_random_mat3f(state);

    Vec3D_f v = btest_random_vec3df(state);
    Vec3D_f lhs = mat3df_vec_mul(mat3df_mul(a, b), v);
    Vec3D_f rhs = mat3df_vec_mul(a, mat3df_vec_mul(b, v));

    return vec3df_equal(lhs, rhs);
}

static bool prop_equal_reflexive(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);

    return mat3df_equal(a, a) != 0;
}

static bool prop_inverse_is_mul_inverse(uint32_t *state)
{
    Mat3_f a = btest_random_mat3f(state);

    Mat3_f inv = mat3df_inverse(a);
    Mat3_f id = mat3df_get_identity();

    return mat3df_equal(mat3df_mul(a, inv), id);
}

static bool prop_rotation_x_det_is_one(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Mat3_f r = mat3df_get_rotation_x(theta);

    return float_eq_approx(mat3df_det(r), 1.0f);
}

static bool prop_rotation_x_composition_adds_angles(uint32_t *state)
{
    float a = btest_randfloat(state);
    float b = btest_randfloat(state);
    Mat3_f combined = mat3df_mul(mat3df_get_rotation_x(a), mat3df_get_rotation_x(b));
    Mat3_f expected = mat3df_get_rotation_x(a + b);

    return mat3df_equal(combined, expected);
}

static bool prop_rotation_x_preserves_length(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Vec3D_f v = btest_random_vec3df(state);
    Vec3D_f rv = mat3df_vec_mul(mat3df_get_rotation_x(theta), v);
    float len_before = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    float len_after = sqrtf(rv.x * rv.x + rv.y * rv.y + rv.z * rv.z);

    return float_eq_approx(len_before, len_after);
}

static bool prop_rotation_y_det_is_one(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Mat3_f r = mat3df_get_rotation_y(theta);

    return float_eq_approx(mat3df_det(r), 1.0f);
}

static bool prop_rotation_y_composition_adds_angles(uint32_t *state)
{
    float a = btest_randfloat(state);
    float b = btest_randfloat(state);
    Mat3_f combined = mat3df_mul(mat3df_get_rotation_y(a), mat3df_get_rotation_y(b));
    Mat3_f expected = mat3df_get_rotation_y(a + b);
    return mat3df_equal(combined, expected);
}

static bool prop_rotation_y_preserves_length(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Vec3D_f v = btest_random_vec3df(state);
    Vec3D_f rv = mat3df_vec_mul(mat3df_get_rotation_y(theta), v);
    float len_before = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    float len_after = sqrtf(rv.x * rv.x + rv.y * rv.y + rv.z * rv.z);

    return float_eq_approx(len_before, len_after);
}

static bool prop_rotation_z_det_is_one(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Mat3_f r = mat3df_get_rotation_z(theta);
    return float_eq_approx(mat3df_det(r), 1.0f);
}

static bool prop_rotation_z_composition_adds_angles(uint32_t *state)
{
    float a = btest_randfloat(state);
    float b = btest_randfloat(state);
    Mat3_f combined = mat3df_mul(mat3df_get_rotation_z(a), mat3df_get_rotation_z(b));
    Mat3_f expected = mat3df_get_rotation_z(a + b);
    return mat3df_equal(combined, expected);
}

static bool prop_rotation_z_preserves_length(uint32_t *state)
{
    float theta = btest_randfloat(state);
    Vec3D_f v = btest_random_vec3df(state);
    Vec3D_f rv = mat3df_vec_mul(mat3df_get_rotation_z(theta), v);
    float len_before = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    float len_after = sqrtf(rv.x * rv.x + rv.y * rv.y + rv.z * rv.z);
    return float_eq_approx(len_before, len_after);
}

static bool prop_scaling_det_matches_factors(uint32_t *state)
{
    float sx = btest_randfloat(state);
    float sy = btest_randfloat(state);
    float sz = btest_randfloat(state);

    Mat3_f s = mat3df_get_scaling(sx, sy, sz);
    return float_eq_approx(mat3df_det(s), sx * sy * sz);
}

static bool prop_scaling_ones_is_identity(uint32_t *state)
{
    (void)state;
    Mat3_f s = mat3df_get_scaling(1.0f, 1.0f, 1.0f);
    Mat3_f id = mat3df_get_identity();

    return mat3df_equal(s, id);
}

static bool prop_reflec_xy_is_involution(uint32_t *state)
{
    (void)state;
    Mat3_f r = mat3df_get_reflec_xy();
    Mat3_f id = mat3df_get_identity();
    return mat3df_equal(mat3df_mul(r, r), id);
}

static bool prop_reflec_xy_det_is_neg_one(uint32_t *state)
{
    (void)state;
    return float_eq_approx(mat3df_det(mat3df_get_reflec_xy()), -1.0f);
}

static bool prop_reflec_yz_is_involution(uint32_t *state)
{
    (void)state;
    Mat3_f r = mat3df_get_reflec_yz();
    Mat3_f id = mat3df_get_identity();
    return mat3df_equal(mat3df_mul(r, r), id);
}

static bool prop_reflec_yz_det_is_neg_one(uint32_t *state)
{
    (void)state;
    return float_eq_approx(mat3df_det(mat3df_get_reflec_yz()), -1.0f);
}

static bool prop_reflec_xz_is_involution(uint32_t *state)
{
    (void)state;
    Mat3_f r = mat3df_get_reflec_xz();
    Mat3_f id = mat3df_get_identity();
    return mat3df_equal(mat3df_mul(r, r), id);
}

static bool prop_reflec_xz_det_is_neg_one(uint32_t *state)
{
    (void)state;
    return float_eq_approx(mat3df_det(mat3df_get_reflec_xz()), -1.0f);
}

static bool prop_shear_x_det_is_one(uint32_t *state)
{
    float xy = btest_randfloat(state);
    float xz = btest_randfloat(state);
    Mat3_f sh = mat3df_get_shear_x(xy, xz);
    return float_eq_approx(mat3df_det(sh), 1.0f);
}

static bool prop_shear_x_zero_is_identity(uint32_t *state)
{
    (void)state;
    Mat3_f sh = mat3df_get_shear_x(0.0f, 0.0f);
    Mat3_f id = mat3df_get_identity();
    return mat3df_equal(sh, id);
}

static bool prop_shear_y_det_is_one(uint32_t *state)
{
    float yx = btest_randfloat(state);
    float yz = btest_randfloat(state);
    Mat3_f sh = mat3df_get_shear_y(yx, yz);
    return float_eq_approx(mat3df_det(sh), 1.0f);
}

static bool prop_shear_y_zero_is_identity(uint32_t *state)
{
    (void)state;
    Mat3_f sh = mat3df_get_shear_y(0.0f, 0.0f);
    Mat3_f id = mat3df_get_identity();
    return mat3df_equal(sh, id);
}

static bool prop_shear_z_det_is_one(uint32_t *state)
{
    float zx = btest_randfloat(state);
    float zy = btest_randfloat(state);
    Mat3_f sh = mat3df_get_shear_z(zx, zy);
    return float_eq_approx(mat3df_det(sh), 1.0f);
}

static bool prop_shear_z_zero_is_identity(uint32_t *state)
{
    (void)state;
    Mat3_f sh = mat3df_get_shear_z(0.0f, 0.0f);
    Mat3_f id = mat3df_get_identity();
    return mat3df_equal(sh, id);
}

BTEST_REGISTER("Mat3_f Identity is Mul Identity", prop_identity_is_mul_identity);
BTEST_REGISTER("Mat3_f Addition Commutativity", prop_add_commutative);
BTEST_REGISTER("Mat3_f Subtraction Self is Zero", prop_sub_self_is_zero);
BTEST_REGISTER("Mat3_f Scalr Distributes Over Addition", prop_scale_distributes_over_add);
BTEST_REGISTER("Mat3_f Transposition is Involution", prop_transpose_is_involution);
BTEST_REGISTER("Mat3_f Multiplication Associativity", prop_mul_associative);
BTEST_REGISTER("Mat3_f Determinant is Multiplicative", prop_det_is_multiplicative);
BTEST_REGISTER("Mat3_f Vector Multiplication Identity", prop_vec_mul_identity);
BTEST_REGISTER("Mat3_f Vector Multiplication Identity", prop_vec_mul_matches_mat_composition);
BTEST_REGISTER("Mat3_f Equal Reflexive", prop_equal_reflexive);
BTEST_REGISTER("Mat3_f Inverse is Multiplication Inverse", prop_inverse_is_mul_inverse);

BTEST_REGISTER("Mat3_f Rotation X Determinant is One", prop_rotation_x_det_is_one);
BTEST_REGISTER("Mat3_f Rotation X Composition Adds Angles", prop_rotation_x_composition_adds_angles);
BTEST_REGISTER("Mat3_f Rotation X Preserves Length", prop_rotation_x_preserves_length);

BTEST_REGISTER("Mat3_f Rotation Y Determinant is One", prop_rotation_y_det_is_one);
BTEST_REGISTER("Mat3_f Rotation Y Composition Adds Angles", prop_rotation_y_composition_adds_angles);
BTEST_REGISTER("Mat3_f Rotation Y Preserves Length", prop_rotation_y_preserves_length);

BTEST_REGISTER("Mat3_f Rotation Z Determinant is One", prop_rotation_z_det_is_one);
BTEST_REGISTER("Mat3_f Rotation Z Composition Adds Angles", prop_rotation_z_composition_adds_angles);
BTEST_REGISTER("Mat3_f Rotation Z Preserves Length", prop_rotation_z_preserves_length);

BTEST_REGISTER("Mat3_f Scaling Determinant Matches Factors", prop_scaling_det_matches_factors);
BTEST_REGISTER("Mat3_f Scaling Ones is Identity", prop_scaling_ones_is_identity);

BTEST_REGISTER("Mat3_f Reflection XY is Involution", prop_reflec_xy_is_involution);
BTEST_REGISTER("Mat3_f Reflection XY is Negative One", prop_reflec_xy_det_is_neg_one);

BTEST_REGISTER("Mat3_f Reflection YZ is Involution", prop_reflec_yz_is_involution);
BTEST_REGISTER("Mat3_f Reflection YZ Determinant is Negative One", prop_reflec_yz_det_is_neg_one);

BTEST_REGISTER("Mat3_f Refelction XZ is Involution", prop_reflec_xz_is_involution);
BTEST_REGISTER("Mat3_f Refelction XZ Determinant is One", prop_reflec_xz_det_is_neg_one);

BTEST_REGISTER("Mat3_f Shear X Determinant is One", prop_shear_x_det_is_one);
BTEST_REGISTER("Mat3_f Shear X Zero is Identity", prop_shear_x_zero_is_identity);

BTEST_REGISTER("Mat3_f Shear Y Determinant is One", prop_shear_y_det_is_one);
BTEST_REGISTER("Mat3_f Shear Y Zero is Identity", prop_shear_y_zero_is_identity);

BTEST_REGISTER("Mat3_f Shear Z Determinant is One", prop_shear_z_det_is_one);
BTEST_REGISTER("Mat3_f Shear Z Zero is Identity", prop_shear_z_zero_is_identity);