#define BIJA_IMPLEMENTATION
#include "../bija_test.h"

Btest_PropertyTest *registry = NULL;
size_t count = 0;
size_t capacity = 0;

int main(void)
{
    uint32_t state = 2463538692;
    btest_pbt_runner(&state);
}