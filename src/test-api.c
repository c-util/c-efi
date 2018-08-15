/*
 * Tests for Public API
 * This simply tests for visibility of all API symbols. It does not invoke any
 * code nor test for fitness for purpose.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c-efi.h"

static void test_api(void) {
        assert(C_EFI_NULL == 0);
}

int main(int argc, char **argv) {
        test_api();
        return 0;
}
