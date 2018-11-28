/*
 * Tests for Public API
 * This simply tests for visibility of all API symbols. It does not invoke any
 * code nor test for fitness for purpose.
 */

#include <assert.h>
#include <stdlib.h>
#include "c-efi.h"

static void test_api(void) {
        assert(!C_EFI_NULL);
        assert(C_EFI_JOIN(1, 1) == 11);
}

int main(int argc, char **argv) {
        test_api();
        return 0;
}
