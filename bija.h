/*******************************************************************************
 *
 * Bija
 * Linear Algebra Library for C
 *
 * -----------------------------------------------------------------------------
 *
 * Description
 * -----------
 * Bija is a small header file library that implements Mathematical functions
 * for 2D vectors, 3D vectors, 4D vectors, 2x2 matrices, and 3x3 matrices.
 *
 * Convention
 * ----------
 *    - Bija's implementation is geared for CPU performance rather than for a
 *      defensive API, hence the implementation will trust IEEE-754 standards
 *      for division by zero logic and for zero by zero division logic.
 *    - Comparing two floats will not be done using == and instead by comparing
 *      the difference of two floats with Bija's own EPSILON value.
 *
 * Features
 * --------
 *    //TODO: Create a list of features that Bija implements
 *
 * Public API
 * ----------
 *    //TODO: Create a list of public functions / defintions within this API
 *
 * Repositiory
 * -----------
 * //TODO: Link the repo here!!!
 *
 * License
 * -------
 * MIT License.
 * See LICENSE for more details.
 *
 * Copyright (c) 2026 Prayag Patel (PrayagPatel1) <prayagpatel283@gmail.com>
 *
 ******************************************************************************/

// Linear Algebra Public Interface
#ifndef BIJA_H
#define BIJA_H

#include <stddef.h>
#include <assert.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ==== Layer 0: Platform Specific Code ==== */
#if defined(__clang__) || defined(__GNUC__)
#define BIJA_FORCE_INLINE static inline __attribute__((always_inline))
#elif defined(__MSC_VER)
#define BIJA_FORCE_INLINE static inline __forceinline
#else
#define BIJA_FORCE_INLINE static inline
#endif

#define BIJA_STATIC_INLINE static inline

    /* ==== Layer 1: Utility Functions ==== */
#define BIJA_EPSILON 1e-6f

    BIJA_FORCE_INLINE float lerp_f(float a, float b, float t);
    BIJA_FORCE_INLINE float clamp_f(float x, float min, float max);
    BIJA_FORCE_INLINE float min_f(float a, float b);
    BIJA_FORCE_INLINE float max_f(float a, float b);
    BIJA_FORCE_INLINE int float_eq_approx(float a, float b);

    /* ==== Layer 2: Core Vector / Matrix Definitions ==== */
    typedef union
    {
        struct
        {
            float x, y;
        };
        float elems[2];
    } Vec2D_f;
    static_assert(sizeof(Vec2D_f) == sizeof(float) * 2, "Vec2D_f has unexpected padding bytes");

    typedef union
    {
        struct
        {
            float x, y, z;
        };
        float elems[3];
    } Vec3D_f;
    static_assert(sizeof(Vec3D_f) == sizeof(float) * 3, "Vec3D_f has unexpected padding bytes");

    typedef union
    {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            float r, g, b, a;
        };
        float elems[4];
    } Vec4D_f;
    static_assert(sizeof(Vec4D_f) == sizeof(float) * 4, "Vec4D_f has unexpected padding bytes");

    typedef struct
    {
        float elems[4];
    } Mat2_f;
    static_assert(sizeof(Mat2_f) == sizeof(float) * 4, "Mat2_f has unexpected padding bytes");

    typedef struct
    {
        float elems[9];
    } Mat3_f;
    static_assert(sizeof(Mat3_f) == sizeof(float) * 9, "Mat3_f has unexpected padding bytes");

    /* ==== Layer 3: Vector Operations ==== */

    BIJA_STATIC_INLINE Vec2D_f vec2df_add(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE Vec2D_f vec2df_sub(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE Vec2D_f vec2df_scale(Vec2D_f vec, float scalar);
    BIJA_STATIC_INLINE float vec2df_dot(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE Vec2D_f vec2df_hadamard_prod(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE Vec2D_f vec2df_hadamard_div(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE Vec2D_f vec2df_negate(Vec2D_f vec);

    BIJA_STATIC_INLINE Vec3D_f vec3df_add(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_sub(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_scale(Vec3D_f vec, float scalar);
    BIJA_STATIC_INLINE float vec3df_dot(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_hadamard_prod(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_hadamard_div(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_negate(Vec3D_f vec);

    BIJA_STATIC_INLINE Vec4D_f vec4df_add(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE Vec4D_f vec4df_sub(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE Vec4D_f vec4df_scale(Vec4D_f vec, float scalar);
    BIJA_STATIC_INLINE float vec4df_dot(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE Vec4D_f vec4df_hadamard_prod(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE Vec4D_f vec4df_hadamard_div(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE Vec4D_f vec4df_negate(Vec4D_f vec);

    BIJA_STATIC_INLINE float vec2df_mag(Vec2D_f vec);
    BIJA_STATIC_INLINE float vec2df_dist(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE float vec2df_angle(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE float vec2df_cross(Vec2D_f vec1, Vec2D_f vec2);

    BIJA_STATIC_INLINE float vec3df_mag(Vec3D_f vec);
    BIJA_STATIC_INLINE float vec3df_dist(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE float vec3df_angle(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_cross(Vec3D_f vec1, Vec3D_f vec2);

    BIJA_STATIC_INLINE float vec4df_mag(Vec4D_f vec);
    BIJA_STATIC_INLINE float vec4df_dist(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE float vec4df_angle(Vec4D_f vec1, Vec4D_f vec2);

    BIJA_STATIC_INLINE Vec2D_f vec2df_floor(Vec2D_f vec);
    BIJA_STATIC_INLINE Vec2D_f vec2df_ceil(Vec2D_f vec);
    BIJA_STATIC_INLINE Vec2D_f vec2df_max(Vec2D_f vec1, Vec2D_f vec2);
    BIJA_STATIC_INLINE Vec2D_f vec2df_min(Vec2D_f vec1, Vec2D_f vec2);

    BIJA_STATIC_INLINE Vec3D_f vec3df_floor(Vec3D_f vec);
    BIJA_STATIC_INLINE Vec3D_f vec3df_ceil(Vec3D_f vec);
    BIJA_STATIC_INLINE Vec3D_f vec3df_max(Vec3D_f vec1, Vec3D_f vec2);
    BIJA_STATIC_INLINE Vec3D_f vec3df_min(Vec3D_f vec, Vec3D_f vec2);

    BIJA_STATIC_INLINE Vec4D_f vec4df_floor(Vec4D_f vec);
    BIJA_STATIC_INLINE Vec4D_f vec4df_ceil(Vec4D_f vec);
    BIJA_STATIC_INLINE Vec4D_f vec4df_max(Vec4D_f vec1, Vec4D_f vec2);
    BIJA_STATIC_INLINE Vec4D_f vec4df_min(Vec4D_f vec1, Vec4D_f vec2);

    BIJA_STATIC_INLINE Vec2D_f vec2df_norm(Vec2D_f vec);
    BIJA_STATIC_INLINE Vec2D_f vec2df_proj(Vec2D_f vec1, Vec2D_f vec2);

    BIJA_STATIC_INLINE Vec3D_f vec3df_norm(Vec3D_f vec);
    BIJA_STATIC_INLINE Vec3D_f vec3df_proj(Vec3D_f vec1, Vec3D_f vec2);

    BIJA_STATIC_INLINE Vec4D_f vec4df_norm(Vec4D_f vec);
    BIJA_STATIC_INLINE Vec4D_f vec4df_proj(Vec4D_f vec1, Vec4D_f vec2);

    BIJA_STATIC_INLINE int vec2df_equal(Vec2D_f vec1, Vec2D_f vec2);

    BIJA_STATIC_INLINE int vec3df_equal(Vec3D_f vec1, Vec3D_f vec2);

    BIJA_STATIC_INLINE int vec4df_equal(Vec4D_f vec1, Vec4D_f vec2);

    /* ==== Layer 4: Matrix Operations ==== */
    BIJA_STATIC_INLINE Mat2_f mat2df_get_identity(void);
    BIJA_STATIC_INLINE Mat2_f mat2df_get_rotation(float rad);
    BIJA_STATIC_INLINE Mat2_f mat2df_get_scaling(float sx, float sy);
    BIJA_STATIC_INLINE Mat2_f mat2df_get_reflec_x(void);
    BIJA_STATIC_INLINE Mat2_f mat2df_get_reflec_y(void);
    BIJA_STATIC_INLINE Mat2_f mat2df_get_shear(float x, float y);

    BIJA_STATIC_INLINE Mat3_f mat3df_get_identity(void);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_rotation_x(float rad);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_rotation_y(float rad);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_rotation_z(float rad);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_scaling(float sx, float sy, float sz);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_reflec_xy(void);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_reflec_yz(void);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_reflec_xz(void);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_shear_x(float xy, float xz);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_shear_y(float yx, float yz);
    BIJA_STATIC_INLINE Mat3_f mat3df_get_shear_z(float zx, float zy);

    BIJA_STATIC_INLINE Mat2_f mat2df_add(Mat2_f mat1, Mat2_f mat2);
    BIJA_STATIC_INLINE Mat2_f mat2df_sub(Mat2_f mat1, Mat2_f mat2);
    BIJA_STATIC_INLINE Mat2_f mat2df_scale(Mat2_f mat, float scalar);
    BIJA_STATIC_INLINE Mat2_f mat2df_mul(Mat2_f mat1, Mat2_f mat2);
    BIJA_STATIC_INLINE Vec2D_f mat2df_vec_mul(Mat2_f mat, Vec2D_f vec);
    BIJA_STATIC_INLINE Mat2_f mat2df_transpose(Mat2_f mat);

    BIJA_STATIC_INLINE Mat3_f mat3df_add(Mat3_f mat1, Mat3_f mat2);
    BIJA_STATIC_INLINE Mat3_f mat3df_sub(Mat3_f mat1, Mat3_f mat2);
    BIJA_STATIC_INLINE Mat3_f mat3df_scale(Mat3_f mat, float scalar);
    BIJA_STATIC_INLINE Mat3_f mat3df_mul(Mat3_f mat1, Mat3_f mat2);
    BIJA_STATIC_INLINE Vec3D_f mat3df_vec_mul(Mat3_f mat, Vec3D_f vec);
    BIJA_STATIC_INLINE Mat3_f mat3df_transpose(Mat3_f mat);

    BIJA_STATIC_INLINE float mat2df_det(Mat2_f mat);
    BIJA_STATIC_INLINE float mat3df_det(Mat3_f mat);

    BIJA_STATIC_INLINE int mat2df_equal(Mat2_f mat1, Mat2_f mat2);
    BIJA_STATIC_INLINE int mat3df_equal(Mat3_f mat1, Mat3_f mat2);

    BIJA_STATIC_INLINE Mat2_f mat2df_inverse(Mat2_f mat);
    BIJA_STATIC_INLINE Mat3_f mat3df_inverse(Mat3_f mat);

#ifdef __cplusplus
}
#endif

#endif // BIJA_H

#ifdef BIJA_IMPLEMENTATION

#include <math.h>

/* ==== Layer 1: Ultility Function Implementations ==== */
BIJA_FORCE_INLINE float lerp_f(float a, float b, float t)
{
    return a + (b - a) * t;
}
BIJA_FORCE_INLINE float clamp_f(float x, float min, float max)
{
    return (x < min) ? min : ((x > max) ? max : x);
}
BIJA_FORCE_INLINE float min_f(float a, float b)
{
    return (a > b) ? b : a;
}
BIJA_FORCE_INLINE float max_f(float a, float b)
{
    return (a < b) ? b : a;
}
BIJA_FORCE_INLINE int float_eq_approx(float a, float b)
{
    float diff = a - b;
    if (diff < 0.0f)
        diff = -diff;
    return diff < BIJA_EPSILON;
}

/* ==== Layer 3: Vector Operation Implementations ==== */
BIJA_STATIC_INLINE void vec_add_internal(const float *x, const float *y, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = x[i] + y[i];
    }
}
BIJA_STATIC_INLINE void vec_sub_internal(const float *x, const float *y, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = x[i] - y[i];
    }
}
BIJA_STATIC_INLINE void vec_scale_internal(const float *x, float *out, const float scalar, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = x[i] * scalar;
    }
}
BIJA_STATIC_INLINE float vec_dot_internal(const float *x, const float *y, const size_t dim)
{
    float sum = 0.0f;
    for (size_t i = 0; i < dim; i++)
    {
        sum += x[i] * y[i];
    }
    return sum;
}
BIJA_STATIC_INLINE void vec_hada_prod_internal(const float *x, const float *y, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = x[i] * y[i];
    }
}
BIJA_STATIC_INLINE void vec_hada_div_internal(const float *x, const float *y, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = x[i] / y[i];
    }
}
BIJA_STATIC_INLINE void vec_floor_internal(const float *x, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = floorf(x[i]);
    }
}
BIJA_STATIC_INLINE void vec_ceil_internal(const float *x, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = ceilf(x[i]);
    }
}
BIJA_STATIC_INLINE void vec_max_internal(const float *x, const float *y, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = max_f(x[i], y[i]);
    }
}
BIJA_STATIC_INLINE void vec_min_internal(const float *x, const float *y, float *out, const size_t dim)
{
    for (size_t i = 0; i < dim; i++)
    {
        out[i] = min_f(x[i], y[i]);
    }
}

BIJA_STATIC_INLINE void mat_identity_internal(float *out, const size_t dim)
{
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            out[y * dim + x] = (x + y % 2 == 0) ? 1.0f : 0.0f;
        }
    }
}
BIJA_STATIC_INLINE void mat_add_internal(const float *mat1, const float *mat2, float *out, const size_t dim)
{
    static_assert(sizeof(mat1) == sizeof(mat2), "mat1 and mat2 must have the same number of rows and columns.");
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            out[y * dim + x] = mat1[y * dim + x] + mat2[y * dim + x];
        }
    }
}
BIJA_STATIC_INLINE void mat_sub_internal(const float *mat1, const float *mat2, float *out, const size_t dim)
{
    static_assert(sizeof(mat1) == sizeof(mat2), "mat1 and mat2 rows and columns must be of the same size");
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            out[y * dim + x] = mat1[y * dim + x] - mat2[y * dim + x];
        }
    }
}
BIJA_STATIC_INLINE void mat_scale_internal(const float *mat, const float scalar, float *out, const size_t dim)
{
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            out[y * dim + x] = mat[y * dim + x] * scalar;
        }
    }
}
BIJA_STATIC_INLINE void mat_mul_internal(const float *mat1, const float *mat2, float *out, const size_t dim)
{
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            float sum = 0.0f;
            for (size_t i = 0; i < dim; i++)
            {
                sum += mat1[x * dim + i] * mat2[i * dim + y];
            }
            out[y * dim + x] = sum;
        }
    }
}
BIJA_STATIC_INLINE void mat_transpose_internal(const float *mat, float *out, const size_t dim)
{
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            out[y * dim + x] = mat[x * dim + y];
        }
    }
}

static void mat_get_submat(const float *mat, float *out, const size_t row_exclude, const size_t col_exclude, const size_t dim)
{
    int sub_col, sub_row = 0;
    for (size_t y = 0; y < dim; y++)
    {
        sub_col = 0;
        if (y == row_exclude)
            continue;
        for (size_t x = 0; x < dim; x++)
        {
            if (x == col_exclude)
                continue;

            out[sub_row * (dim - 1) + sub_col] = mat[y * dim + x];
            sub_col++;
        }
        sub_row++;
    }
}
BIJA_STATIC_INLINE float mat_det_internal(const float *mat, const size_t dim)
{
    if (dim == 1)
    {
        return mat[0];
    }
    else if (dim == 2)
    {
        return mat[0] * mat[3] - mat[1] * mat[2];
    }

    float det = 0.0f;
    int sign = 1;
    float sub_mat[(dim - 1) * (dim - 1)];

    for (size_t i = 0; i < dim; i++)
    {
        mat_get_submat(mat, sub_mat, 0, i, dim);
        det += sign * mat[0 * dim + i] * mat_det_internal(sub_mat, dim - 1);

        sign *= -1;
    }

    return det;
}

static void mat_get_cofactor(const float *mat, float *out, const size_t dim)
{
    if (dim == 2)
    {
        for (size_t y = 0; y < dim; y++)
        {
            for (size_t x = 0; x < dim; x++)
            {
                out[y * dim + x] = (x + y % 2 == 0) ? mat[(1 - x) * dim + (1 - x)] : mat[y * dim + x] * -1;
            }
        }
        return;
    }

    float sub_mat[dim * dim];
    int sign = 1;
    for (size_t y = 0; y < dim; y++)
    {
        for (size_t x = 0; x < dim; x++)
        {
            mat_get_submat(mat, sub_mat, y, x, dim);
            out[y * dim + x] = sign * mat_det_internal(sub_mat, dim - 1);
            sign *= -1;
        }
    }
}
BIJA_STATIC_INLINE void mat_inverse_internal(const float *mat, float *out, const size_t dim)
{
    assert(sizeof(mat) == dim * dim * sizeof(float));

    float idet = 1.0f / mat_det_internal(mat, dim);
    mat_get_cofactor(mat, out, dim);
    mat_transpose_internal(mat, out, dim);

    for (size_t i = 0; i < dim * dim; i++)
    {
        out[i] *= idet;
    }
}

BIJA_STATIC_INLINE Vec2D_f vec2df_add(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f result = {0};
    vec_add_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_sub(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f result = {0};
    vec_sub_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_scale(Vec2D_f vec, float scalar)
{
    Vec2D_f result = {0};
    vec_scale_internal(vec.elems, result.elems, scalar, 2);
    return result;
}
BIJA_STATIC_INLINE float vec2df_dot(Vec2D_f vec1, Vec2D_f vec2)
{
    return vec_dot_internal(vec1.elems, vec2.elems, 2);
}
BIJA_STATIC_INLINE Vec2D_f vec2df_hadamard_prod(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f result = {0};
    vec_hada_prod_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_hadamard_div(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f result = {0};
    vec_hada_div_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_negate(Vec2D_f vec)
{
    return vec2df_scale(vec, -1.0f);
}

BIJA_STATIC_INLINE Vec3D_f vec3df_add(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    vec_add_internal(vec1.elems, vec2.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_sub(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    vec_sub_internal(vec1.elems, vec2.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_scale(Vec3D_f vec, float scalar)
{
    Vec3D_f result = {0};
    vec_scale_internal(vec.elems, result.elems, scalar, 3);
    return result;
}
BIJA_STATIC_INLINE float vec3df_dot(Vec3D_f vec1, Vec3D_f vec2)
{
    return vec_dot_internal(vec1.elems, vec2.elems, 3);
}
BIJA_STATIC_INLINE Vec3D_f vec3df_hadamard_prod(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    vec_hada_prod_internal(vec1.elems, vec2.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_hadamard_div(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    vec_hada_div_internal(vec1.elems, vec2.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_negate(Vec3D_f vec)
{
    return vec3df_scale(vec, -1.0f);
}

BIJA_STATIC_INLINE Vec4D_f vec4df_add(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f result = {0};
    vec_add_internal(vec1.elems, vec2.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_sub(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f result = {0};
    vec_sub_internal(vec1.elems, vec2.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_scale(Vec4D_f vec, float scalar)
{
    Vec4D_f result = {0};
    vec_scale_internal(vec.elems, result.elems, scalar, 4);
    return result;
}
BIJA_STATIC_INLINE float vec4df_dot(Vec4D_f vec1, Vec4D_f vec2)
{
    return vec_dot_internal(vec1.elems, vec2.elems, 4);
}
BIJA_STATIC_INLINE Vec4D_f vec4df_hadamard_prod(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f result = {0};
    vec_hada_prod_internal(vec1.elems, vec2.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_hadamard_div(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f result = {0};
    vec_hada_div_internal(vec1.elems, vec2.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_negate(Vec4D_f vec)
{
    return vec4df_scale(vec, -1.0f);
}

BIJA_STATIC_INLINE float vec2df_mag(Vec2D_f vec)
{
    return sqrtf(vec2df_dot(vec, vec));
}
BIJA_STATIC_INLINE float vec2df_dist(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f diff = vec2df_sub(vec1, vec2);
    return sqrtf(vec2df_dot(diff, diff));
}
BIJA_STATIC_INLINE float vec2df_angle(Vec2D_f vec1, Vec2D_f vec2)
{
    float numerator = vec2df_dot(vec1, vec2);
    float denominator = vec2df_mag(vec1) * vec2df_mag(vec2);
    return acosf(numerator / denominator);
}
BIJA_STATIC_INLINE float vec2df_cross(Vec2D_f vec1, Vec2D_f vec2)
{
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

BIJA_STATIC_INLINE float vec3df_mag(Vec3D_f vec)
{
    return sqrtf(vec3df_dot(vec, vec));
}
BIJA_STATIC_INLINE float vec3df_dist(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f diff = vec3df_sub(vec1, vec2);
    return sqrtf(vec3df_dot(diff, diff));
}
BIJA_STATIC_INLINE float vec3df_angle(Vec3D_f vec1, Vec3D_f vec2)
{
    float numerator = vec3df_dot(vec1, vec2);
    float denominator = vec3df_mag(vec1) * vec3df_mag(vec2);
    return acosf(numerator / denominator);
}
BIJA_STATIC_INLINE Vec3D_f vec3df_cross(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = vec1.x * vec2.z - vec1.z * vec2.x;
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return result;
}

BIJA_STATIC_INLINE float vec4df_mag(Vec4D_f vec)
{
    return sqrtf(vec4df_dot(vec, vec));
}
BIJA_STATIC_INLINE float vec4df_dist(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f diff = vec4df_sub(vec1, vec2);
    return sqrtf(vec4df_dot(diff, diff));
}
BIJA_STATIC_INLINE float vec4df_angle(Vec4D_f vec1, Vec4D_f vec2)
{
    float numerator = vec4df_dot(vec1, vec2);
    float denominator = vec4df_mag(vec1) * vec4df_mag(vec2);
    return acosf(numerator / denominator);
}

BIJA_STATIC_INLINE Vec2D_f vec2df_floor(Vec2D_f vec)
{
    Vec2D_f result = {0};
    vec_floor_internal(vec.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_ceil(Vec2D_f vec)
{
    Vec2D_f result = {0};
    vec_ceil_internal(vec.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_max(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f result = {0};
    vec_max_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_min(Vec2D_f vec1, Vec2D_f vec2)
{
    Vec2D_f result = {0};
    vec_min_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}

BIJA_STATIC_INLINE Vec3D_f vec3df_floor(Vec3D_f vec)
{
    Vec3D_f result = {0};
    vec_floor_internal(vec.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_ceil(Vec3D_f vec)
{
    Vec3D_f result = {0};
    vec_ceil_internal(vec.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_max(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    vec_max_internal(vec1.elems, vec2.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_min(Vec3D_f vec1, Vec3D_f vec2)
{
    Vec3D_f result = {0};
    vec_min_internal(vec1.elems, vec2.elems, result.elems, 3);
    return result;
}

BIJA_STATIC_INLINE Vec4D_f vec4df_floor(Vec4D_f vec)
{
    Vec4D_f result = {0};
    vec_floor_internal(vec.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_ceil(Vec4D_f vec)
{
    Vec4D_f result = {0};
    vec_ceil_internal(vec.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_max(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f result = {0};
    vec_max_internal(vec1.elems, vec2.elems, result.elems, 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_min(Vec4D_f vec1, Vec4D_f vec2)
{
    Vec4D_f result = {0};
    vec_min_internal(vec1.elems, vec2.elems, result.elems, 2);
    return result;
}

BIJA_STATIC_INLINE Vec2D_f vec2df_norm(Vec2D_f vec)
{
    Vec2D_f result = {0};
    vec_scale_internal(vec.elems, result.elems, 1.0f / vec2df_mag(vec), 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f vec2df_proj(Vec2D_f vec1, Vec2D_f vec2)
{
    float numer = vec2df_dot(vec1, vec2);
    float denom = powf(vec2df_mag(vec2), 2);
    return vec2df_scale(vec2, numer / denom);
}

BIJA_STATIC_INLINE Vec3D_f vec3df_norm(Vec3D_f vec)
{
    Vec3D_f result = {0};
    vec_scale_internal(vec.elems, result.elems, 1.0f / vec3df_mag(vec), 3);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f vec3df_proj(Vec3D_f vec1, Vec3D_f vec2)
{
    float numer = vec3df_dot(vec1, vec2);
    float denom = powf(vec3df_mag(vec2), 2);
    return vec3df_scale(vec2, numer / denom);
}

BIJA_STATIC_INLINE Vec4D_f vec4df_norm(Vec4D_f vec)
{
    Vec4D_f result = {0};
    vec_scale_internal(vec.elems, result.elems, 1.0f / vec4df_mag(vec), 4);
    return result;
}
BIJA_STATIC_INLINE Vec4D_f vec4df_proj(Vec4D_f vec1, Vec4D_f vec2)
{
    float numer = vec4df_dot(vec1, vec2);
    float denom = powf(vec4df_mag(vec2), 2);
    return vec4df_scale(vec2, numer / denom);
}

BIJA_STATIC_INLINE int vec2df_equal(Vec2D_f vec1, Vec2D_f vec2)
{
    return float_eq_approx(vec1.x, vec2.x) && float_eq_approx(vec1.y, vec2.y);
}

BIJA_STATIC_INLINE int vec3df_equal(Vec3D_f vec1, Vec3D_f vec2)
{
    return float_eq_approx(vec1.x, vec2.x) &&
           float_eq_approx(vec1.y, vec2.y) &&
           float_eq_approx(vec1.z, vec2.z);
}

BIJA_STATIC_INLINE int vec4df_equal(Vec4D_f vec1, Vec4D_f vec2)
{
    return float_eq_approx(vec1.x, vec2.x) &&
           float_eq_approx(vec1.y, vec2.y) &&
           float_eq_approx(vec1.z, vec2.z) &&
           float_eq_approx(vec1.w, vec2.w);
}

/* ==== Matrix Operation Implementation ==== */

BIJA_STATIC_INLINE Mat2_f mat2df_get_identity(void)
{
    Mat2_f result = {0};
    mat_identity_internal(result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_get_rotation(float rad)
{
    Mat2_f result = {0};
    result.elems[0] = cosf(rad);
    result.elems[1] = -sinf(rad);
    result.elems[2] = sinf(rad);
    result.elems[3] = cosf(rad);
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_get_scaling(float sx, float sy)
{
    Mat2_f result = {0};
    result.elems[0] = sx;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;
    result.elems[3] = sy;
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_get_reflec_x(void)
{
    Mat2_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;
    result.elems[3] = -1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_get_reflec_y(void)
{
    Mat2_f result = {0};
    result.elems[0] = -1.0f;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;
    result.elems[3] = 1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_get_shear(float x, float y)
{
    Mat2_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = x;
    result.elems[2] = y;
    result.elems[3] = 1.0f;
    return result;
}

BIJA_STATIC_INLINE Mat3_f mat3df_get_identity(void)
{
    Mat3_f result = {0};
    mat_identity_internal(result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_rotation_x(float rad)
{
    Mat3_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;

    result.elems[3] = 0.0f;
    result.elems[4] = cosf(rad);
    result.elems[5] = -sinf(rad);

    result.elems[6] = 0.0f;
    result.elems[7] = sinf(rad);
    result.elems[8] = cosf(rad);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_rotation_y(float rad)
{
    Mat3_f result = {0};
    result.elems[0] = cosf(rad);
    result.elems[1] = 0.0f;
    result.elems[2] = sinf(rad);

    result.elems[3] = 0.0f;
    result.elems[4] = 1.0f;
    result.elems[5] = 0.0f;

    result.elems[6] = -sinf(rad);
    result.elems[7] = 0.0f;
    result.elems[8] = cosf(rad);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_rotation_z(float rad)
{
    Mat3_f result = {0};
    result.elems[0] = cosf(rad);
    result.elems[1] = -sinf(rad);
    result.elems[2] = 0.0f;

    result.elems[3] = sinf(rad);
    result.elems[4] = cosf(rad);
    result.elems[5] = 0.0f;

    result.elems[6] = 0.0f;
    result.elems[7] = 0.0f;
    result.elems[8] = 1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_scaling(float sx, float sy, float sz)
{
    Mat3_f result = {0};
    result.elems[0] = sx;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;

    result.elems[0] = 0.0f;
    result.elems[0] = sy;
    result.elems[0] = 0.0f;

    result.elems[0] = 0.0f;
    result.elems[0] = 0.0f;
    result.elems[0] = sz;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_reflec_xy(void)
{
    Mat3_f result = {0};
    result.elems[0] = 1.0;
    result.elems[1] = 0.0f;
    result.elems[3] = 0.0f;

    result.elems[4] = 0.0f;
    result.elems[5] = 1.0f;
    result.elems[6] = 0.0f;

    result.elems[7] = 0.0f;
    result.elems[8] = 0.0f;
    result.elems[9] = -1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_reflec_yz(void)
{
    Mat3_f result = {0};
    result.elems[0] = -1.0f;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;

    result.elems[3] = 0.0f;
    result.elems[4] = 1.0f;
    result.elems[5] = 0.0f;

    result.elems[6] = 0.0f;
    result.elems[7] = 0.0f;
    result.elems[8] = 1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_reflec_xz(void)
{
    Mat3_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;

    result.elems[3] = 0.0f;
    result.elems[4] = -1.0f;
    result.elems[5] = 0.0f;

    result.elems[6] = 0.0f;
    result.elems[7] = 0.0f;
    result.elems[8] = 1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_shear_x(float xy, float xz)
{
    Mat3_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = xy;
    result.elems[2] = xz;

    result.elems[3] = 0.0f;
    result.elems[4] = 1.0f;
    result.elems[5] = 0.0f;

    result.elems[6] = 0.0f;
    result.elems[7] = 0.0f;
    result.elems[8] = 1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_shear_y(float yx, float yz)
{
    Mat3_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = yx;
    result.elems[2] = 0.0f;

    result.elems[3] = 0.0f;
    result.elems[4] = 1.0f;
    result.elems[5] = 0.0f;

    result.elems[6] = 0.0f;
    result.elems[7] = yz;
    result.elems[8] = 1.0f;
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_get_shear_z(float zx, float zy)
{
    Mat3_f result = {0};
    result.elems[0] = 1.0f;
    result.elems[1] = 0.0f;
    result.elems[2] = 0.0f;

    result.elems[3] = 0.0f;
    result.elems[4] = 1.0f;
    result.elems[5] = 0.0f;

    result.elems[6] = zx;
    result.elems[7] = zy;
    result.elems[8] = 1.0f;
    return result;
}

BIJA_STATIC_INLINE Mat2_f mat2df_add(Mat2_f mat1, Mat2_f mat2)
{
    Mat2_f result = {0};
    mat_add_internal(mat1.elems, mat2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_sub(Mat2_f mat1, Mat2_f mat2)
{
    Mat2_f result = {0};
    mat_sub_internal(mat1.elems, mat2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_scale(Mat2_f mat, float scalar)
{
    Mat2_f result = {0};
    mat_scale_internal(mat.elems, scalar, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_mul(Mat2_f mat1, Mat2_f mat2)
{
    Mat2_f result = {0};
    mat_mul_internal(mat1.elems, mat2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec2D_f mat2df_vec_mul(Mat2_f mat, Vec2D_f vec)
{
    Vec2D_f result = {0};
    mat_mul_internal(mat.elems, vec.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat2_f mat2df_transpose(Mat2_f mat)
{
    Mat2_f result = {0};
    mat_transpose_internal(mat.elems, result.elems, 2);
    return result;
}

BIJA_STATIC_INLINE Mat3_f mat3df_add(Mat3_f mat1, Mat3_f mat2)
{
    Mat3_f result = {0};
    mat_add_internal(mat1.elems, mat2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_sub(Mat3_f mat1, Mat3_f mat2)
{
    Mat3_f result = {0};
    mat_sub_internal(mat1.elems, mat2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_scale(Mat3_f mat, float scalar)
{
    Mat3_f result = {0};
    mat_scale_internal(mat.elems, scalar, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_mul(Mat3_f mat1, Mat3_f mat2)
{
    Mat3_f result = {0};
    mat_mul_internal(mat1.elems, mat2.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Vec3D_f mat3df_vec_mul(Mat3_f mat, Vec3D_f vec)
{
    Vec3D_f result = {0};
    mat_mul_internal(mat.elems, vec.elems, result.elems, 3);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_transpose(Mat3_f mat)
{
    Mat3_f result = {0};
    mat_transpose_internal(mat.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE float mat2df_det(Mat2_f mat)
{
    return mat_det_internal(mat.elems, 2);
}
BIJA_STATIC_INLINE float mat3df_det(Mat3_f mat)
{
    return mat_det_internal(mat.elems, 2);
}

BIJA_STATIC_INLINE int mat2df_equal(Mat2_f mat1, Mat2_f mat2)
{
    return float_eq_approx(mat1.elems[0], mat2.elems[0]) &&
           float_eq_approx(mat1.elems[1], mat2.elems[1]) &&
           float_eq_approx(mat1.elems[2], mat2.elems[2]) &&
           float_eq_approx(mat1.elems[3], mat2.elems[3]);
}
BIJA_STATIC_INLINE int mat3df_equal(Mat3_f mat1, Mat3_f mat2)
{
    return float_eq_approx(mat1.elems[0], mat2.elems[0]) &&
           float_eq_approx(mat1.elems[1], mat2.elems[1]) &&
           float_eq_approx(mat1.elems[2], mat2.elems[2]) &&
           float_eq_approx(mat1.elems[3], mat2.elems[3]) &&
           float_eq_approx(mat1.elems[4], mat2.elems[4]) &&
           float_eq_approx(mat1.elems[5], mat2.elems[5]) &&
           float_eq_approx(mat1.elems[6], mat2.elems[6]) &&
           float_eq_approx(mat1.elems[7], mat2.elems[7]) &&
           float_eq_approx(mat1.elems[8], mat2.elems[8]);
}

BIJA_STATIC_INLINE Mat2_f mat2df_inverse(Mat2_f mat)
{
    Mat2_f result = {0};
    mat_inverse_internal(mat.elems, result.elems, 2);
    return result;
}
BIJA_STATIC_INLINE Mat3_f mat3df_inverse(Mat3_f mat)
{
    Mat3_f result = {0};
    mat_inverse_internal(mat.elems, result.elems, 3);
    return result;
}

#endif // BIJA_IMPLEMENTATION
