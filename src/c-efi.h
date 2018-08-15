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

#ifdef __cplusplus
}
#endif
