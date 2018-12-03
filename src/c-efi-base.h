#pragma once

/**
 * UEFI Base Environment
 *
 * This header defines the base environment for UEFI development. It provides
 * types and macros as declared in the UEFI specification, as well as de-facto
 * standard additions provided by the reference implementation by Intel.
 *
 * Since UEFI environments are significantly different from common operating
 * system environments, the base environment differs as well. It would be
 * technically possible to port common C Standard Libraries (e.g., glibc) to an
 * UEFI environment. However, this would undermine many of the characteristics
 * of the UEFI environment, and prevent usage of several features the UEFI
 * model brings. Therefore, this project provides an alternative to a standard
 * C library for UEFI, but it also serves as base for possibly implementing (or
 * porting) a standard C library for/to UEFI.
 *
 * Please be aware that as long as you do not employ a standard C library for
 * UEFI, you most likely are unable to link against common C libraries. Almost
 * all existing C libraries use the standard library in some way, and this will
 * make them incompatible with UEFI environments.
 *
 * This header provides the base types and macros used throughout the project.
 * It provides basic fixed-size integers, a NULL-equivalent, booleans, standard
 * UEFI types, and more. All symbols are prefixed with `C_EFI_*` or `CEfi*`.
 *
 * You are highly recommended to conduct the UEFI Specification for details on
 * the programming environment. Following a summary of key parts from the
 * specification:
 *
 *  * All integers are either fixed-size, or native size. That is, either use
 *    CEfi{8,..,64} and CEfiU{8,..,64} directly, or use the native-size
 *    CEfiSize and CEfiUSize. Native size integers are sized according to the
 *    architecture restrictions. You should assume they are pointer-sized.
 *
 *    Whenever you refer to memory (either pointing to it, or remember the size
 *    of a memory block), the native size integers should be your tool of
 *    choice.
 *
 *  * Even though the CPU might run in any endianness, all stored data is
 *    little-endian. That means, if you encounter integers split into
 *    byte-arrays (e.g., `CEfiDevicePathProtocol.length`), you must assume it
 *    is little-endian encoded. But if you encounter native integers, you must
 *    assume they are encoded in native endianness.
 *    For now the UEFI specification only defines little-endian architectures,
 *    hence this did not pop up as actual issue. Future extensions might change
 *    this, though.
 *
 *  * The C-language-calling-convention is used. If you configure your compiler
 *    correctly, you should be good to go. The UEFI Specification defines some
 *    additional common rules for all its APIs, though. You will most likely
 *    not see any of these mentioned in the individual API documentions,
 *    though.
 *
 *     - Pointers must reference physical-memory locations (no I/O mappings, no
 *       virtual addresses, etc.). Once ExitBootServices() was called, and the
 *       virtual address mapping was set, you must provide virtual-memory
 *       locations instead.
 *     - Pointers must be correctly aligned.
 *     - NULL is disallowed, unless explicitly mentioned otherwise.
 *     - Data referenced by pointers is undefined on error-return from a
 *       function.
 *     - You must not pass data larger than native-size (sizeof(CEfiUSize)) on
 *       the stack. You must pass them by reference.
 *
 *  * Stack size is at least 128KiB and 16-byte aligned. All stack space might
 *    be marked non-executable! Once ExitBootServices() was called, you must
 *    guarantee at least 4KiB of stack space, 16-byte aligned for all runtime
 *    services you call.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The UEFI Specification has several circular type dependencies. We simply use
 * forward declarations to get the required types in-scope. We really try to
 * limit the number of circular type dependencies, so make sure to only add
 * them here if really necessary.
 */
typedef struct CEfiDevicePathProtocol CEfiDevicePathProtocol;
typedef struct CEfiSimpleTextInputProtocol CEfiSimpleTextInputProtocol;
typedef struct CEfiSimpleTextOutputProtocol CEfiSimpleTextOutputProtocol;
typedef struct CEfiSystemTable CEfiSystemTable;

/**
 * C_EFI_NULL: NULL symbol
 *
 * Since NULL is defined by stdint.h, we need an equivalent. We follow what
 * everyone else does and define it as ((void *)0).
 */
#define C_EFI_NULL ((void *)0)

/**
 * C_EFI_JOIN: Join two compiler symbols
 * @_a:		First symbol
 * @_b:		Second symbol
 *
 * This joins two compiler symbols via the `a ## b` preprocessor construct. It
 * first resolves the arguments to their values, then concatenates them.
 */
#define C_EFI_JOIN(_a, _b) C_EFI_JOIN_LITERALS(_a, _b)
#define C_EFI_JOIN_LITERALS(_a, _b) _a ## _b

/**
 * CEfiI8, CEfiU8, CEfiI16, CEfiU16,
 * CEfiI32, CEfiU32, CEfiI64, CEfiU64: Fixed size integers
 *
 * The CEfiI* and CEfiU* fixed size integers are UEFI equivalents to uint*_t
 * from stdint.h in ISO-C. Note that we rely on `__INTX_TYPE__` to be defined
 * by your compiler. This is what is used in most stdint.h implementations as
 * well.
 *
 * Other compiler-constants known from ISO-C are defined as well, including for
 * instance the UINTX_C() equivalents for fixed size integers.
 *
 * Note: UEFI provides 128-bit types as well, but most compilers lack support
 *       to expose the required types. We simply skip their definition. If the
 *       need arises, we can reconsider and add them.
 */

#if !defined(__INT8_TYPE__) || \
    !defined(__UINT8_TYPE__) || \
    !defined(__INT16_TYPE__) || \
    !defined(__UINT16_TYPE__) || \
    !defined(__INT32_TYPE__) || \
    !defined(__UINT32_TYPE__) || \
    !defined(__INT64_TYPE__) || \
    !defined(__UINT64_TYPE__) || \
    (!defined(__INT8_C) && !defined(__INT8_C_SUFFIX__)) || \
    (!defined(__INT16_C) && !defined(__INT16_C_SUFFIX__)) || \
    (!defined(__INT32_C) && !defined(__INT32_C_SUFFIX__)) || \
    (!defined(__INT64_C) && !defined(__INT64_C_SUFFIX__)) || \
    (!defined(__UINT8_C) && !defined(__UINT8_C_SUFFIX__)) || \
    (!defined(__UINT16_C) && !defined(__UINT16_C_SUFFIX__)) || \
    (!defined(__UINT32_C) && !defined(__UINT32_C_SUFFIX__)) || \
    (!defined(__UINT64_C) && !defined(__UINT64_C_SUFFIX__))
#  error "Compiler does not provide fixed-size integer macros."
#endif

typedef __INT8_TYPE__ CEfiI8;
typedef __UINT8_TYPE__ CEfiU8;
typedef __INT16_TYPE__ CEfiI16;
typedef __UINT16_TYPE__ CEfiU16;
typedef __INT32_TYPE__ CEfiI32;
typedef __UINT32_TYPE__ CEfiU32;
typedef __INT64_TYPE__ CEfiI64;
typedef __UINT64_TYPE__ CEfiU64;

#if defined(__INT8_C_SUFFIX__)
#  define C_EFI_I8_C(_v) C_EFI_JOIN(_v, __INT8_C_SUFFIX__)
#  define C_EFI_U8_C(_v) C_EFI_JOIN(_v, __UINT8_C_SUFFIX__)
#  define C_EFI_I16_C(_v) C_EFI_JOIN(_v, __INT16_C_SUFFIX__)
#  define C_EFI_U16_C(_v) C_EFI_JOIN(_v, __UINT16_C_SUFFIX__)
#  define C_EFI_I32_C(_v) C_EFI_JOIN(_v, __INT32_C_SUFFIX__)
#  define C_EFI_U32_C(_v) C_EFI_JOIN(_v, __UINT32_C_SUFFIX__)
#  define C_EFI_I64_C(_v) C_EFI_JOIN(_v, __INT64_C_SUFFIX__)
#  define C_EFI_U64_C(_v) C_EFI_JOIN(_v, __UINT64_C_SUFFIX__)
#else
#  define C_EFI_I8_C(_v) __INT8_C(_v)
#  define C_EFI_U8_C(_v) __UINT8_C(_v)
#  define C_EFI_I16_C(_v) __INT16_C(_v)
#  define C_EFI_U16_C(_v) __UINT16_C(_v)
#  define C_EFI_I32_C(_v) __INT32_C(_v)
#  define C_EFI_U32_C(_v) __UINT32_C(_v)
#  define C_EFI_I64_C(_v) __INT64_C(_v)
#  define C_EFI_U64_C(_v) __UINT64_C(_v)
#endif

/**
 * CEfiISize, CEfiUSize: Native sized integers
 *
 * The CEfiISize and CEfiUSize types are native-size integer types. They
 * always have the same size as the target-architecture instruction width as
 * defined by the UEFI specification ('instruction width' is the wording of the
 * specification, and effectively means the pointer and address width).
 */
typedef __INTPTR_TYPE__ CEfiISize;
typedef __UINTPTR_TYPE__ CEfiUSize;

/**
 * CEfiBool: Boolean Type
 *
 * The CEfiBool type corresponds to the C11 definition of the _Bool type. It
 * is a simple typedef.
 */
typedef _Bool CEfiBool;

/**
 * C_EFI_TRUE, C_EFI_FALSE: Boolean values
 *
 * Both constants, C_EFI_TRUE and C_EFI_FALSE, follow the C11 standard for
 * the `true' and `false' constants defined in `stdbool.h'.
 */
#define C_EFI_TRUE 1
#define C_EFI_FALSE 0

/**
 * CEfiChar8, CEfiChar16: Character Types
 *
 * The CEfiChar8 type is an unsigned 8-byte integer type that stores 8-bit
 * ASCII compatible characters (or character strings), using the ISO-Latin-1
 * character set.
 *
 * The CEfiChar16 type is an unsigned 16-byte integer type that stores
 * characters (or character strings) compatible to the UCS-2 encoding.
 */
typedef CEfiU8 CEfiChar8;
typedef CEfiU16 CEfiChar16;

/**
 * CEfiGuid: Globally Unique Identifier Type
 *
 * The CEfiGuid type represents a GUID. It is always 128bit in size and
 * aligned to 64bit. Only its binary representation is guaranteed to be stable.
 * You are highly recommended to only ever access the `u8' version of it.
 *
 * The @ms1 to @ms4 fields can be used to encode Microsoft-style GUIDs, where
 * @ms1, @ms2, and @ms3 are little-endian encoded.
 */
typedef struct CEfiGuid {
        union {
                _Alignas(8) CEfiU8 u8[16];
                _Alignas(8) CEfiU16 u16[8];
                _Alignas(8) CEfiU32 u32[4];
                _Alignas(8) CEfiU64 u64[2];
                struct {
                        _Alignas(8) CEfiU32 ms1;
                        CEfiU16 ms2;
                        CEfiU16 ms3;
                        CEfiU8 ms4[8];
                };
        };
} CEfiGuid;

#define C_EFI_GUID(_ms1, _ms2, _ms3,                                            \
                   _ms4, _ms5, _ms6, _ms7,                                      \
                   _ms8, _ms9, _ms10, _ms11)                                    \
        ((struct CEfiGuid){                                                     \
                .ms1 = (_ms1),                                                  \
                .ms2 = (_ms2),                                                  \
                .ms3 = (_ms3),                                                  \
                .ms4 = {                                                        \
                        (_ms4), (_ms5), (_ms6), (_ms7),                         \
                        (_ms8), (_ms9), (_ms10), (_ms11),                       \
                },                                                              \
        })

/**
 * CEfiMacAddress, CEfiIpv4Address,
 * CEfiIpv6Address, CEfiIpAddress: Networking Types
 *
 * These types represent the corresponding networking entities. CEfiMacAddress,
 * CEfiIpv4Address, and CEfiIpv6Address are mere byte-buffers. CEfiIpAddress is
 * a 16-byte buffer, but required to be 4-byte aligned.
 */

typedef struct CEfiMacAddress {
        CEfiU8 u8[32];
} CEfiMacAddress;

typedef struct CEfiIpv4Address {
        CEfiU8 u8[4];
} CEfiIpv4Address;

typedef struct CEfiIpv6Address {
        CEfiU8 u8[16];
} CEfiIpv6Address;

typedef struct CEfiIpAddress {
        union {
                _Alignas(4) CEfiIpv4Address ipv4;
                _Alignas(4) CEfiIpv6Address ipv6;
        };
} CEfiIpAddress;

/**
 * CEfiStatus, CEfiHandle, CEfiEvent, CEfiLba, CEfiTpl, CEfiPhysicalAddress,
 * CEfiVirtualAddress: Common UEFI Aliases
 *
 * These types are all aliases as defined by the UEFI specification. They are
 * solely meant for documentational purposes.
 *
 * CEfiStatus is used for status returns of function calls. CEfiHandle
 * represents handles to allocated objects. CEfiEvent represents slots that
 * can be waited on (like Windows events). CEfiLba represents logical block
 * addresses. CEfiTpl represents thread priority levels. CEfiPhysicalAddress,
 * and CEfiVirtualAddress are used to denote physical, and virtual addresses.
 */
typedef CEfiUSize CEfiStatus;
typedef void *CEfiHandle;
typedef void *CEfiEvent;
typedef CEfiU64 CEfiLba;
typedef CEfiUSize CEfiTpl;
typedef CEfiU64 CEfiPhysicalAddress;
typedef CEfiU64 CEfiVirtualAddress;

/**
 * CEfiImageEntryPoint: Type of image entry points
 *
 * All loaded images must have an entry point of this type. The entry point is
 * pointed to in the PE/COFF header. No particular symbol-name is required,
 * though most setups automatically pick the function named `efi_main`.
 *
 * On load, the entry-point is called with a pointer to the own image as first
 * argument, a pointer to the global system table as second argument. Normal
 * applications are unloaded when this function returns. Drivers might stay in
 * memory, depending on the return type. See the specification for details.
 */
typedef CEfiStatus (*CEfiImageEntryPoint)(CEfiHandle image, CEfiSystemTable *st);

#ifdef __cplusplus
}
#endif
