#pragma once

/**
 * UEFI Protocol - Loaded Image
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>

#define C_EFI_LOADED_IMAGE_PROTOCOL_GUID C_EFI_GUID(0x5B1B31A1, 0x9562, 0x11d2, 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B)

#define C_EFI_LOADED_IMAGE_PROTOCOL_REVISION C_EFI_U32_C(0x1000)

typedef struct CEfiLoadedImageProtocol {
        CEfiU32 revision;
        CEfiHandle parent_handle;
        CEfiSystemTable *system_table;

        CEfiHandle device_handle;
        CEfiDevicePathProtocol *file_path;
        void *reserved;

        CEfiU32 load_options_size;
        void *load_options;

        void *image_base;
        CEfiU64 image_size;
        CEfiMemoryType image_code_type;
        CEfiMemoryType image_data_type;

        CEfiStatus (*unload) (CEfiHandle image_handle);
} CEfiLoadedImageProtocol;

#ifdef __cplusplus
}
#endif
