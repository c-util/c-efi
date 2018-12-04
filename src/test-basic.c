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
         * Verify some status codes with constants taken directly from the
         * spec. Note that CEfiStatus depends on CEfiUSize, as such matches the
         * target architecture word width.
         */
        {
                assert(!C_EFI_SUCCESS);
                assert(sizeof(C_EFI_SUCCESS) == sizeof(CEfiStatus));
                assert(!C_EFI_ERROR(C_EFI_SUCCESS));
                assert(C_EFI_ERROR(C_EFI_UNSUPPORTED));

                if (sizeof(CEfiStatus) == sizeof(uint32_t)) {
                        assert((uint32_t)C_EFI_UNSUPPORTED == (uint32_t)0x80000003UL);
                } else if (sizeof(CEfiStatus) == sizeof(uint64_t)) {
                        assert((uint64_t)C_EFI_UNSUPPORTED == (uint64_t)0x8000000000000003UL);
                } else {
                        assert(0);
                }
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

        /*
         * Verify alignments and size of networking types.
         */
        {
                assert(_Alignof(CEfiMacAddress) == 1);
                assert(_Alignof(CEfiIpv4Address) == 1);
                assert(_Alignof(CEfiIpv6Address) == 1);
                assert(_Alignof(CEfiIpAddress) == 4);

                assert(sizeof(CEfiMacAddress) == 32);
                assert(sizeof(CEfiIpv4Address) == 4);
                assert(sizeof(CEfiIpv6Address) == 16);
                assert(sizeof(CEfiIpAddress) == 16);
        }
}

int main(int argc, char **argv) {
        test_basic();
        return 0;
}
