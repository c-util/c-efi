#pragma once

/**
 * UEFI Protocol - Simple Text Input Ex
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>

typedef struct CEfiSimpleTextInputExProtocol CEfiSimpleTextInputExProtocol;

#define C_EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID C_EFI_GUID(0xdd9e7534, 0x7762, 0x4698, 0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa)

#define C_EFI_TOGGLE_STATE_VALID        C_EFI_U8_C(0x80)
#define C_EFI_KEY_STATE_EXPOSED         C_EFI_U8_C(0x40)
#define C_EFI_SCROLL_LOCK_ACTIVE        C_EFI_U8_C(0x01)
#define C_EFI_NUM_LOCK_ACTIVE           C_EFI_U8_C(0x02)
#define C_EFI_CAPS_LOCK_ACTIVE          C_EFI_U8_C(0x04)

typedef CEfiU8 CEfiKeyToggleState;

#define C_EFI_SHIFT_STATE_VALID         C_EFI_U32_C(0x80000000)
#define C_EFI_RIGHT_SHIFT_PRESSED       C_EFI_U32_C(0x00000001)
#define C_EFI_LEFT_SHIFT_PRESSED        C_EFI_U32_C(0x00000002)
#define C_EFI_RIGHT_CONTROL_PRESSED     C_EFI_U32_C(0x00000004)
#define C_EFI_LEFT_CONTROL_PRESSED      C_EFI_U32_C(0x00000008)
#define C_EFI_RIGHT_ALT_PRESSED         C_EFI_U32_C(0x00000010)
#define C_EFI_LEFT_ALT_PRESSED          C_EFI_U32_C(0x00000020)
#define C_EFI_RIGHT_LOGO_PRESSED        C_EFI_U32_C(0x00000040)
#define C_EFI_LEFT_LOGO_PRESSED         C_EFI_U32_C(0x00000080)
#define C_EFI_MENU_KEY_PRESSED          C_EFI_U32_C(0x00000100)
#define C_EFI_SYS_REQ_PRESSED           C_EFI_U32_C(0x00000200)

typedef struct CEfiKeyState {
        CEfiU32 key_shift_state;
        CEfiKeyToggleState key_toggle_state;
} CEfiKeyState;

typedef struct CEfiKeyData {
        CEfiInputKey key;
        CEfiKeyState key_state;
} CEfiKeyData;

typedef CEfiStatus (*CEfiKeyNotifyFunction) (CEfiKeyData *key_data);

typedef struct CEfiSimpleTextInputExProtocol {
        CEfiStatus (*reset) (CEfiSimpleTextInputExProtocol *this_,
                             CEfiBool extended_verification);
        CEfiStatus (*read_key_stroke_ex) (CEfiSimpleTextInputExProtocol *this_,
                                          CEfiKeyData *key_data);
        CEfiEvent wait_for_key_ex;
        CEfiStatus (*set_state) (CEfiSimpleTextInputExProtocol *this_,
                                CEfiKeyToggleState *key_toggle_state);
        CEfiStatus (*register_key_notify) (CEfiSimpleTextInputExProtocol *this_,
                                           CEfiKeyData *key_data,
                                           CEfiKeyNotifyFunction key_notification_function,
                                           void **notify_handle);
        CEfiStatus (*unregister_key_notify) (CEfiSimpleTextInputExProtocol *this_,
                                             void *notification_handle);
} CEfiSimpleTextInputExProtocol;

#ifdef __cplusplus
}
#endif
