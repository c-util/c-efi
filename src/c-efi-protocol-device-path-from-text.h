#pragma once

/**
 * UEFI Protocol - Device Path From Text
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>
#include <c-efi-protocol-device-path.h>

#define C_EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID C_EFI_GUID(0x5c99a21, 0xc70f, 0x4ad2, 0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e)

typedef struct CEfiDevicePathFromTextProtocol {
        CEfiDevicePathProtocol *(*convert_text_to_device_node) (CEfiChar16 *text_device_node);
        CEfiDevicePathProtocol *(*convert_text_to_device_path) (CEfiChar16 *text_device_path);
} CEfiDevicePathFromTextProtocol;

#ifdef __cplusplus
}
#endif
