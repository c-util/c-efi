#pragma once

/**
 * UEFI Protocol - Simple Text Input
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>

#define C_EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID C_EFI_GUID(0x387477c1, 0x69c7, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)

typedef struct CEfiInputKey {
        CEfiU16 scan_code;
        CEfiChar16 unicode_char;
} CEfiInputKey;

typedef struct CEfiSimpleTextInputProtocol {
        CEfiStatus (*reset) (CEfiSimpleTextInputProtocol *this_,
                             CEfiBool extended_verification);
        CEfiStatus (*read_key_stroke) (CEfiSimpleTextInputProtocol *this_,
                                       CEfiInputKey *key);
        CEfiEvent wait_for_key;
} CEfiSimpleTextInputProtocol;

#ifdef __cplusplus
}
#endif
