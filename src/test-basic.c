/*
 * Basic Functionality Tests
 */

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c-efi.h"

static void test_basic(void) {
        /*
         * Verify basic types and definitions. These should all be
         * straightforward.
         */
        {
                assert(C_EFI_NULL == NULL);
                assert(C_EFI_NULL == 0);

                assert(sizeof(CEfiI8) == 1);
                assert(sizeof(CEfiU8) == 1);
                assert(sizeof(CEfiI16) == 2);
                assert(sizeof(CEfiU16) == 2);
                assert(sizeof(CEfiI32) == 4);
                assert(sizeof(CEfiU32) == 4);
                assert(sizeof(CEfiI64) == 8);
                assert(sizeof(CEfiU64) == 8);

                assert(C_EFI_I8_C(0) == 0);
                assert(C_EFI_U8_C(0) == 0);
                assert(C_EFI_I16_C(0) == 0);
                assert(C_EFI_U16_C(0) == 0);
                assert(C_EFI_I32_C(0) == 0);
                assert(C_EFI_U32_C(0) == 0);
                assert(C_EFI_I64_C(0) == 0);
                assert(C_EFI_U64_C(0) == 0);

                assert(sizeof(CEfiISize) == sizeof(void *));
                assert(sizeof(CEfiUSize) == sizeof(void *));

                assert(sizeof(CEfiChar8) == sizeof(CEfiU8));
                assert(sizeof(CEfiChar16) == sizeof(CEfiU16));
        }

        /*
         * Intel defines BOOLEAN as UINT8, so make sure we are binary
         * compatible.
         */
        {
                assert(sizeof(CEfiBool) == sizeof(uint8_t));
                assert(C_EFI_TRUE);
                assert(!C_EFI_FALSE);
                assert((int)C_EFI_TRUE == 1);
                assert((int)C_EFI_FALSE == 0);
        }

        /*
         * Verify alignment and size of GUID is correct. The type itself is
         * required to be 64bit aligned, 128bit in size.
         */
        {
                CEfiGuid id = {};

                assert(_Alignof(CEfiGuid) >= 8);
                assert(_Alignof(id) >= 8);
                assert(_Alignof(id.u8) >= 8);
                assert(_Alignof(id.u16) >= 8);
                assert(_Alignof(id.u32) >= 8);
                assert(_Alignof(id.u64) >= 8);

                assert(sizeof(CEfiGuid) == 16);
                assert(sizeof(id) == 16);
                assert(sizeof(id.u8) == 16);
                assert(sizeof(id.u16) == 16);
                assert(sizeof(id.u32) == 16);
                assert(sizeof(id.u64) == 16);
        }
}

int main(int argc, char **argv) {
        test_basic();
        return 0;
}
