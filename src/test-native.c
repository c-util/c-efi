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

CEfiStatus efi_main(CEfiHandle h, CEfiSystemTable *st) {
        return test_native();
}
