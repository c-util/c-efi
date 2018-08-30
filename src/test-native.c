/*
 * Basic Native UEFI Tests
 */

#include "c-efi.h"

#define ASSERT_RETURN(_expr) {                                                  \
                if (!(_expr))                                                   \
                        return -1;                                              \
        }

static int test_native(void) {
        ASSERT_RETURN(!C_EFI_NULL);

        return 0;
}

int efi_main(void) {
        return test_native();
}
