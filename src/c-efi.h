#pragma once

/**
 * UEFI Reference Specification Protocol Constants and Definitions
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

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

/**
 * CEfiStatus, CEfiHandle, CEfiEvent, CEfiLba, CEfiTpl,
 * CEfiPhysicalAddress, CEfiLogicalAddress: Common UEFI Aliases
 *
 * These types are all aliases as defined by the UEFI specification. They are
 * solely meant for documentational purposes.
 *
 * CEfiStatus is used for status returns of function calls. CEfiHandle
 * represents handles to allocated objects. CEfiEvent represents slots that
 * can be waited on (like Windows events). CEfiLba represents logical block
 * addresses. CEfiTpl represents thread priority levels. CEfiPhysicalAddress
 * and CEfiLogicalAddress are used to denote physical and logical addresses.
 */
typedef CEfiUSize CEfiStatus;
typedef void *CEfiHandle;
typedef void *CEfiEvent;
typedef CEfiU64 CEfiLba;
typedef CEfiUSize CEfiTpl;
typedef CEfiU64 CEfiPhysicalAddress;
typedef CEfiU64 CEfiLogicalAddress;

#ifdef __cplusplus
}
#endif
