#pragma once

/**
 * UEFI Reference Specification Protocol Constants and Definitions
 *
 * This project provides a basic UEFI environment as well as the definitions of
 * protocol constants from the UEFI Specification. The c-efi-base.h header
 * provides the basic programming environment that is necessary once you
 * compile without a Standard C Library. The c-efi-system.h header provides the
 * UEFI system integration including global vtables and types. All remaining
 * functionality is provided in UEFI protocols.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>
#include <c-efi-protocol-device-path.h>
#include <c-efi-protocol-device-path-from-text.h>
#include <c-efi-protocol-device-path-to-text.h>
#include <c-efi-protocol-device-path-utility.h>
#include <c-efi-protocol-loaded-image.h>
#include <c-efi-protocol-loaded-image-device-path.h>

#ifdef __cplusplus
}
#endif
