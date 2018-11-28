#pragma once

/**
 * UEFI Protocol - Device Path To Text
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>
#include <c-efi-protocol-device-path.h>

#define C_EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID C_EFI_GUID(0x8b843e20, 0x8132, 0x4852, 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c)

typedef struct CEfiDevicePathToTextProtocol {
        CEfiChar16 *(*convert_device_node_to_text) (CEfiDevicePathProtocol *device_node,
                                                    CEfiBool display_only,
                                                    CEfiBool allow_shortcuts);
        CEfiChar16 *(*convert_device_path_to_text) (CEfiDevicePathProtocol *device_path,
                                                    CEfiBool display_only,
                                                    CEfiBool allow_shortcuts);
} CEfiDevicePathToTextProtocol;

#ifdef __cplusplus
}
#endif
