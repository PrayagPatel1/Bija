# Bija

> [!WARNING]
> BIJA IS STILL UNDER DEVELOPMENT AND ANYTHIN CAN CHANGE. USE IT AT YOUR OWN RISK.

Bija is a single header linear algebra library developed in C that focusses on
portability, ease of use, and code that works well with the CPU.

Bija can be used within any C project by first defining the `BIJA_IMPLEMENTATION`
macro and then including the library. Since the entire library is in a single header
file, it can be copy pasted into any repo's codebase.

The core types that Bija supports are the following:

1. 2D Vectors (Vec2D_f)
2. 3D Vectors (Vec3D_f)
3. 4D Vectors (Vec4D_f)
4. 2 x 2 Matrix (Mat2_f)
5. 3 x 3 Matrix (Mat3_f)

All of these core types are known at compile time and are implemented in floats
only as of now.

## Example

```C
#define BIJA_IMPLEMENTATION
#include "bija.h"

int main(void)
{
    Mat2_f mat_a = {.elems={1.0f, 2.0f, 3.0f, 4.0f}};
    Mat2_f mat_b = {.elems={5.0f, 6.0f, 7.0f, 8.0f}};

    Mat2_f sum = mat2df_add(mat_a, mat_b);
    Mat2_f sum_det = mat2df_det(sum);

    mat2df_display(sum, "Sum Matrix");
    printf("Sum Matrix Determinant: %f\n", sum_det);
    return 0;
}
```

```console
Sum Matrix
    6.0   8.0
    10.0  12.0
Sum Matrix Determinant: -8
```

## PBT Test Build Instructions

To build the PBT runner to test all of the core types currently avaliable enter
the following commands in you shell:

```console
$ chmod +x build.sh
$ ./build.sh test
```

To run the tests you must navigate to the tests/property_based_tests/bin and
execute the pbt_runner executable:

```console
$ cd tests/property_based_tests/bin
$ ./pbt_runner
```

## Use of LLM

LLM's was used to timeline the entire project.

## References

Shear Mapping Definition: https://en.wikipedia.org/wiki/Shear_mapping
