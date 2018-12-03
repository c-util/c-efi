#pragma once

/**
 * UEFI Protocol - Simple Text Output
 *
 * XXX
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>
#include <c-efi-system.h>

#define C_EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID C_EFI_GUID(0x387477c2, 0x69c7, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b)

typedef struct CEfiSimpleTextOutputMode {
        CEfiI32 max_mode;
        CEfiI32 mode;
        CEfiI32 attribute;
        CEfiI32 cursor_column;
        CEfiI32 cursor_row;
        CEfiBool cursor_visible;
} CEfiSimpleTextOutputMode;

#define C_EFI_BLACK             C_EFI_U8_C(0x00)
#define C_EFI_BLUE              C_EFI_U8_C(0x01)
#define C_EFI_GREEN             C_EFI_U8_C(0x02)
#define C_EFI_CYAN              C_EFI_U8_C(0x03)
#define C_EFI_RED               C_EFI_U8_C(0x04)
#define C_EFI_MAGENTA           C_EFI_U8_C(0x05)
#define C_EFI_BROWN             C_EFI_U8_C(0x06)
#define C_EFI_LIGHTGRAY         C_EFI_U8_C(0x07)
#define C_EFI_BRIGHT            C_EFI_U8_C(0x08)
#define C_EFI_DARKGRAY          (C_EFI_BLACK    | C_EFI_BRIGHT)
#define C_EFI_LIGHTBLUE         (C_EFI_BLUE     | C_EFI_BRIGHT)
#define C_EFI_LIGHTGREEN        (C_EFI_GREEN    | C_EFI_BRIGHT)
#define C_EFI_LIGHTCYAN         (C_EFI_CYAN     | C_EFI_BRIGHT)
#define C_EFI_LIGHTRED          (C_EFI_RED      | C_EFI_BRIGHT)
#define C_EFI_LIGHTMAGENTA      (C_EFI_MAGENTA  | C_EFI_BRIGHT)
#define C_EFI_YELLOW            (C_EFI_BROWN    | C_EFI_BRIGHT)
#define C_EFI_WHITE             C_EFI_U8_C(0x0f)

#define C_EFI_BACKGROUND_BLACK          C_EFI_U8_C(0x00)
#define C_EFI_BACKGROUND_BLUE           C_EFI_U8_C(0x10)
#define C_EFI_BACKGROUND_GREEN          C_EFI_U8_C(0x20)
#define C_EFI_BACKGROUND_CYAN           C_EFI_U8_C(0x30)
#define C_EFI_BACKGROUND_RED            C_EFI_U8_C(0x40)
#define C_EFI_BACKGROUND_MAGENTA        C_EFI_U8_C(0x50)
#define C_EFI_BACKGROUND_BROWN          C_EFI_U8_C(0x60)
#define C_EFI_BACKGROUND_LIGHTGRAY      C_EFI_U8_C(0x70)

typedef struct CEfiSimpleTextOutputProtocol {
        CEfiStatus (CEFICALL *reset) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiBool extended_verification
        );
        CEfiStatus (CEFICALL *output_string) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiChar16 *string
        );
        CEfiStatus (CEFICALL *test_string) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiChar16 *string
        );
        CEfiStatus (CEFICALL *query_mode) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiUSize mode_number,
                CEfiUSize *columns,
                CEfiUSize *rows
        );
        CEfiStatus (CEFICALL *set_mode) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiUSize mode_number
        );
        CEfiStatus (CEFICALL *set_attribute) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiUSize attribute
        );
        CEfiStatus (CEFICALL *clear_screen) (
                CEfiSimpleTextOutputProtocol *this_
        );
        CEfiStatus (CEFICALL *set_cursor_position) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiUSize column,
                CEfiUSize row
        );
        CEfiStatus (CEFICALL *enable_cursor) (
                CEfiSimpleTextOutputProtocol *this_,
                CEfiBool visible
        );
        CEfiSimpleTextOutputMode *mode;
} CEfiSimpleTextOutpuProtocol;

#ifdef __cplusplus
}
#endif
