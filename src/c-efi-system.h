#pragma once

/**
 * UEFI System Integration
 *
 * This header defines the structures and types of the surrounding system of an
 * UEFI application. It contains the definitions of the system table, the
 * runtime and boot services, as well as common types.
 *
 * We do not document the behavior of each of these types and functions. They
 * follow the UEFI specification, which does a well-enough job of documenting
 * each. This file just provides you the C definitions of each symbol and some
 * limited hints on some pecularities.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <c-efi-base.h>

/*
 * Time Management
 *
 * UEFI time management is modeled around the CEfiTime structure, which
 * represents any arbitrary timestamp. The runtime and boot services provide
 * helper functions to query and set the system time.
 */

#define C_EFI_TIME_ADJUST_DAYLIGHT C_EFI_U8_C(0x01)
#define C_EFI_TIME_IN_DAYLIGHT C_EFI_U8_C(0x02)

#define C_EFI_UNSPECIFIED_TIMEZONE C_EFI_I16_C(0x07ff)

typedef struct CEfiTime {
        CEfiU16 year;
        CEfiU8 month;
        CEfiU8 day;
        CEfiU8 hour;
        CEfiU8 minute;
        CEfiU8 second;
        CEfiU8 pad1;
        CEfiU32 nanosecond;
        CEfiI16 timezone;
        CEfiU8 daylight;
        CEfiU8 pad2;
} CEfiTime;

typedef struct CEfiTimeCapabilities {
        CEfiU32 resolution;
        CEfiU32 accuracy;
        CEfiBool sets_to_zero;
} CEfiTimeCapabilities;

/*
 * UEFI Variables
 *
 * UEFI systems provide a way to store global variables. These can be
 * persistent or volatile. The variable store must be provided by the platform,
 * but persistent storage might not be available.
 */

#define C_EFI_VARIABLE_NON_VOLATILE                             C_EFI_U32_C(0x00000001)
#define C_EFI_VARIABLE_BOOTSERVICE_ACCESS                       C_EFI_U32_C(0x00000002)
#define C_EFI_VARIABLE_RUNTIME_ACCESS                           C_EFI_U32_C(0x00000004)
#define C_EFI_VARIABLE_HARDWARE_ERROR_RECORD                    C_EFI_U32_C(0x00000008)
#define C_EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS               C_EFI_U32_C(0x00000010)
#define C_EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS    C_EFI_U32_C(0x00000020)
#define C_EFI_VARIABLE_APPEND_WRITE                             C_EFI_U32_C(0x00000040)
#define C_EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS            C_EFI_U32_C(0x00000080)

#define C_EFI_VARIABLE_AUTHENTICATION_3_CERT_ID_SHA256 C_EFI_U32_C(1)

typedef struct CEfiVariableAuthentication3CertId {
        CEfiU8 type;
        CEfiU32 id_size;
        CEfiU8 id[];
} CEfiVariableAuthentication3CertId;

typedef struct CEfiVariableAuthentication {
        CEfiU64 monotonic_count;
        CEfiU8 auth_info[]; /* WIN_CERTIFICATE_UEFI_ID from PE/COFF */
} CEfiVariableAuthentication;

typedef struct CEfiVariableAuthentication2 {
        CEfiTime timestamp;
        CEfiU8 auth_info[]; /* WIN_CERTIFICATE_UEFI_ID from PE/COFF */
} CEfiVariableAuthentication2;

#define C_EFI_VARIABLE_AUTHENTICATION_3_TIMESTAMP_TYPE C_EFI_U32_C(1)
#define C_EFI_VARIABLE_AUTHENTICATION_3_NONCE_TYPE C_EFI_U32_C(2)

typedef struct CEfiVariableAuthentication3 {
        CEfiU8 version;
        CEfiU8 type;
        CEfiU32 metadata_size;
        CEfiU32 flags;
} CEfiVariableAuthentication3;

typedef struct CEfiVariableAuthentication3Nonce {
        CEfiU32 nonce_size;
        CEfiU8 nonce[];
} CEfiVariableAuthentication3Nonce;

#define C_EFI_HARDWARE_ERROR_VARIABLE_GUID C_EFI_GUID(0x414E6BDD, 0xE47B, 0x47cc, 0xB2, 0x44, 0xBB, 0x61, 0x02, 0x0C, 0xF5, 0x16)

/*
 * Virtual Mappings
 *
 * UEFI runs in an 1-to-1 mapping from virtual to physical addresses. But once
 * you exit boot services, you can apply any address mapping you want, as long
 * as you inform UEFI about it (or, alternatively, stop using the UEFI runtime
 * services).
 */

#define C_EFI_OPTIONAL_POINTER C_EFI_U32_C(0x00000001)

/*
 * System Reset
 *
 * UEFI provides access to firmware functions to reset the system. This
 * includes a wide variety of different possible resets.
 */

typedef enum CEfiResetType {
        C_EFI_RESET_COLD,
        C_EFI_RESET_WARM,
        C_EFI_RESET_SHUTDOWN,
        C_EFI_RESET_PLATFORM_SPECIFIC,
        _C_EFI_RESET_N,
} CEfiResetType;

/*
 * Update Capsules
 *
 * The process of firmware updates is generalized in UEFI. There are small
 * blobs called capsules that you can push into the firmware to be run either
 * immediately or on next reboot.
 */

typedef struct CEfiCapsuleBlockDescriptor {
        CEfiU64 length;
        union {
                CEfiPhysicalAddress data_block;
                CEfiPhysicalAddress continuation_pointer;
        };
} CEfiCapsuleBlockDescriptor;

#define C_EFI_CAPSULE_FLAGS_PERSIST_ACROSS_RESET        C_EFI_U32(0x00010000)
#define C_EFI_CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE       C_EFI_U32(0x00020000)
#define C_EFI_CAPSULE_FLAGS_INITIATE_RESET              C_EFI_U32(0x00040000)

typedef struct CEfiCapsuleHeader {
        CEfiGuid capsule_guid;
        CEfiU32 header_size;
        CEfiU32 flags;
        CEfiU32 capsule_image_size;
} CEfiCapsuleHeader;

#define C_EFI_OS_INDICATIONS_BOOT_TO_FW_UI                      C_EFI_U64_C(0x0000000000000001)
#define C_EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION               C_EFI_U64_C(0x0000000000000002)
#define C_EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED    C_EFI_U64_C(0x0000000000000004)
#define C_EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED              C_EFI_U64_C(0x0000000000000008)
#define C_EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED       C_EFI_U64_C(0x0000000000000010)
#define C_EFI_OS_INDICATIONS_START_OS_RECOVERY                  C_EFI_U64_C(0x0000000000000020)
#define C_EFI_OS_INDICATIONS_START_PLATFORM_RECOVERY            C_EFI_U64_C(0x0000000000000040)

#define C_EFI_CAPSULE_REPORT_GUID C_EFI_GUID(0x39b68c46, 0xf7fb, 0x441b, 0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3)

typedef struct CEfiCapsuleResultVariableHeader {
        CEfiU32 variable_total_size;
        CEfiU32 reserved;
        CEfiGuid capsule_guid;
        CEfiTime capsule_processed;
        CEfiStatus capsule_status;
} CEfiCapsuleResultVariableHeader;

typedef struct CEfiCapsuleResultVariableFMP {
        CEfiU16 version;
        CEfiU8 payload_index;
        CEfiU8 update_image_index;
        CEfiGuid update_image_type_id;
        CEfiChar16 capsule_file_name_and_target[];
} CEfiCapsuleResultVariableFMP;

/*
 * Tasks
 *
 * UEFI uses a simplified task model, and only ever runs on a single CPU.
 * Usually, there is only one single task running on the system, which is the
 * current execution. No interrupts are supported, other than timer interrupts.
 * That is, all device management must be reliant on polling.
 *
 * You can, however, register callbacks to be run by the UEFI core. That is,
 * either when execution is returned to the UEFI core, or when a timer
 * interrupt fires, the scheduler will run the highest priority task next,
 * interrupting the current task. You can use simple task-priority-levels (TPL)
 * to adjust the priority of your callbacks and current task.
 */

#define C_EFI_EVT_TIMER                                 C_EFI_U32_C(0x80000000)
#define C_EFI_EVT_RUNTIME                               C_EFI_U32_C(0x40000000)
#define C_EFI_EVT_NOTIFY_WAIT                           C_EFI_U32_C(0x00000100)
#define C_EFI_EVT_NOTIFY_SIGNAL                         C_EFI_U32_C(0x00000200)
#define C_EFI_EVT_SIGNAL_EXIT_BOOT_SERVICES             C_EFI_U32_C(0x00000201)
#define C_EFI_EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE         C_EFI_U32_C(0x60000202)

typedef void (*CEfiEventNotify) (CEfiEvent event, void *context);

#define C_EFI_EVENT_GROUP_EXIT_BOOT_SERVICES            C_EFI_GUID(0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf)
#define C_EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE        C_EFI_GUID(0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96)
#define C_EFI_EVENT_GROUP_MEMORY_MAP_CHANGE             C_EFI_GUID(0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab)
#define C_EFI_EVENT_GROUP_READY_TO_BOOT                 C_EFI_GUID(0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0x0d, 0x2b)
#define C_EFI_EVENT_GROUP_RESET_SYSTEM                  C_EFI_GUID(0x62da6a56, 0x13fb, 0x485a, 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b)

typedef enum CEfiTimerDelay {
        C_EFI_TIMER_CANCEL,
        C_EFI_TIMER_PERIODIC,
        C_EFI_TIMER_RELATIVE,
} CEfiTimerDelay;

#define C_EFI_TPL_APPLICATION           4
#define C_EFI_TPL_CALLBACK              8
#define C_EFI_TPL_NOTIFY                16
#define C_EFI_TPL_HIGH_LEVEL            31

/*
 * Memory management
 *
 * The UEFI boot services provide you pool-allocation helpers to reserve
 * memory. The region for each allocation can be selected by the caller,
 * allowing to reserve memory that even survives beyond boot services. However,
 * dynamic allocations can only performed via boot services, so no dynamic
 * modifications can be done once you exit boot services.
 */

typedef enum CEfiAllocateType {
        C_EFI_ALLOCATE_ANY_PAGES,
        C_EFI_ALLOCATE_MAX_ADDRESS,
        C_EFI_ALLOCATE_ADDRESS,
        _C_EFI_ALLOCATE_TYPE_N,
} CEfiAllocateType;

typedef enum CEfiMemoryType {
        C_EFI_RESERVED_MEMORY_TYPE,
        C_EFI_LOADER_CODE,
        C_EFI_LOADER_DATA,
        C_EFI_BOOT_SERVICES_CODE,
        C_EFI_BOOT_SERVICES_DATA,
        C_EFI_RUNTIME_SERVICES_CODE,
        C_EFI_RUNTIME_SERVICES_DATA,
        C_EFI_CONVENTIONAL_MEMORY,
        C_EFI_UNUSABLE_MEMORY,
        C_EFI_ACPI_RECLAIM_MEMORY,
        C_EFI_ACPI_MEMORY_NVS,
        C_EFI_MEMORY_MAPPED_IO,
        C_EFI_MEMORY_MAPPED_IO_PORT_SPACE,
        C_EFI_PAL_CODE,
        C_EFI_PERSISTENT_MEMORY,
        _C_EFI_MEMORY_TYPE_N,
} CEfiMemoryType;

#define C_EFI_MEMORY_UC                 C_EFI_U64_C(0x0000000000000001)
#define C_EFI_MEMORY_WC                 C_EFI_U64_C(0x0000000000000002)
#define C_EFI_MEMORY_WT                 C_EFI_U64_C(0x0000000000000004)
#define C_EFI_MEMORY_WB                 C_EFI_U64_C(0x0000000000000008)
#define C_EFI_MEMORY_UCE                C_EFI_U64_C(0x0000000000000010)
#define C_EFI_MEMORY_WP                 C_EFI_U64_C(0x0000000000001000)
#define C_EFI_MEMORY_RP                 C_EFI_U64_C(0x0000000000002000)
#define C_EFI_MEMORY_XP                 C_EFI_U64_C(0x0000000000004000)
#define C_EFI_MEMORY_NV                 C_EFI_U64_C(0x0000000000008000)
#define C_EFI_MEMORY_MORE_RELIABLE      C_EFI_U64_C(0x0000000000010000)
#define C_EFI_MEMORY_RO                 C_EFI_U64_C(0x0000000000020000)
#define C_EFI_MEMORY_RUNTIME            C_EFI_U64_C(0x8000000000000000)

#define C_EFI_MEMORY_DESCRIPTOR_VERSION C_EFI_U32_C(0x00000001)

typedef struct CEfiMemoryDescriptor {
        CEfiU32 type;
        CEfiPhysicalAddress physical_start;
        CEfiVirtualAddress virtual_start;
        CEfiU64 number_of_pages;
        CEfiU64 attribute;
} CEfiMemoryDescriptor;

/*
 * Protocol Management
 *
 * The UEFI driver model provides ways to have bus-drivers, device-drivers, and
 * applications as separate, independent entities. They use protocols to
 * communicate, and handles to refer to common state. Drivers and devices can
 * be registered dynamically at runtime, and can support hotplugging.
 */

typedef enum CEfiInterfaceType {
        C_EFI_NATIVE_INTERFACE,
} CEfiInterfaceType;

typedef enum CEfiLocateSearchType {
        C_EFI_ALL_HANDLES,
        C_EFI_BY_REGISTER_NOTIFY,
        C_EFI_BY_PROTOCOL,
} CEfiLocateSearchType;

#define C_EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL          C_EFI_U32_C(0x00000001)
#define C_EFI_OPEN_PROTOCOL_GET_PROTOCOL                C_EFI_U32_C(0x00000002)
#define C_EFI_OPEN_PROTOCOL_TEST_PROTOCOL               C_EFI_U32_C(0x00000004)
#define C_EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER         C_EFI_U32_C(0x00000008)
#define C_EFI_OPEN_PROTOCOL_BY_DRIVER                   C_EFI_U32_C(0x00000010)
#define C_EFI_OPEN_PROTOCOL_EXCLUSIVE                   C_EFI_U32_C(0x00000020)

typedef struct CEfiOpenProtocolInformationEntry {
        CEfiHandle agent_handle;
        CEfiHandle controller_handle;
        CEfiU32 attributes;
        CEfiU32 open_count;
} CEfiOpenProtocolInformationEntry;

/*
 * Configuration Tables
 *
 * The system table contains an array of auxiliary tables, indexed by their
 * GUID, called configuration tables. Each table uses the generic
 * CEfiConfigurationTable structure as header.
 */

typedef struct CEfiConfigurationTable {
        CEfiGuid vendor_guid;
        void *vendor_table;
} CEfiConfigurationTable;

#define C_EFI_PROPERTIES_TABLE_GUID C_EFI_GUID(0x880aaca3, 0x4adc, 0x4a04, 0x90, 0x79, 0xb7, 0x47, 0x34, 0x8, 0x25, 0xe5)
#define C_EFI_PROPERTIES_TABLE_VERSION C_EFI_U32_C(0x00010000)

#define C_EFI_PROPERTIES_RUNTIME_MEMORY_PROTECTION_NON_EXECUTABLE_PE_DATA C_EFI_U64_C(0x1)

typedef struct CEfiPropertiesTable {
        CEfiU32 version;
        CEfiU32 length;
        CEfiU64 memory_protection_attribute;
} CEfiPropertiesTable;

#define C_EFI_MEMORY_ATTRIBUTES_TABLE_GUID C_EFI_GUID(0xdcfa911d, 0x26eb, 0x469f, 0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20)
#define C_EFI_MEMORY_ATTRIBUTES_TABLE_VERSION C_EFI_U32_C(0x00000001)

typedef struct CEfiMemoryAttributesTable {
        CEfiU32 version;
        CEfiU32 number_of_entries;
        CEfiU32 descriptor_size;
        CEfiU32 reserved;
        CEfiMemoryDescriptor entry[];
} CEfiMemoryAttributesTable;

/*
 * Global Tables
 *
 * UEFI uses no global state, so all access to UEFI internal state is done
 * through vtables you get passed to your entry-point. The global entry is the
 * system-table, which encorporates several sub-tables, including the runtime
 * and boot service tables, and configuration tables (including vendor
 * extensions).
 */

#define C_EFI_2_70_SYSTEM_TABLE_REVISION ((2 << 16) | (70))
#define C_EFI_2_60_SYSTEM_TABLE_REVISION ((2 << 16) | (60))
#define C_EFI_2_50_SYSTEM_TABLE_REVISION ((2 << 16) | (50))
#define C_EFI_2_40_SYSTEM_TABLE_REVISION ((2 << 16) | (40))
#define C_EFI_2_31_SYSTEM_TABLE_REVISION ((2 << 16) | (31))
#define C_EFI_2_30_SYSTEM_TABLE_REVISION ((2 << 16) | (30))
#define C_EFI_2_20_SYSTEM_TABLE_REVISION ((2 << 16) | (20))
#define C_EFI_2_10_SYSTEM_TABLE_REVISION ((2 << 16) | (10))
#define C_EFI_2_00_SYSTEM_TABLE_REVISION ((2 << 16) | ( 0))
#define C_EFI_1_10_SYSTEM_TABLE_REVISION ((1 << 16) | (10))
#define C_EFI_1_02_SYSTEM_TABLE_REVISION ((1 << 16) | ( 2))
#define C_EFI_SPECIFICATION_VERSION C_EFI_SYSTEM_TABLE_REVISION
#define C_EFI_SYSTEM_TABLE_REVISION C_EFI_2_70_SYSTEM_TABLE_REVISION
#define C_EFI_RUNTIME_SERVICES_REVISION C_EFI_SPECIFICATION_VERSION
#define C_EFI_BOOT_SERVICES_REVISION C_EFI_SPECIFICATION_VERSION

typedef struct CEfiTableHeader {
        CEfiU64 signature;
        CEfiU32 revision;
        CEfiU32 header_size;
        CEfiU32 crc32;
        CEfiU32 reserved;
} CEfiTableHeader;

#define C_EFI_RUNTIME_TABLE_SIGNATURE C_EFI_U64_C(0x56524553544e5552) /* "RUNTSERV" */

typedef struct CEfiRuntimeServices {
        CEfiTableHeader hdr;

        CEfiStatus (*get_time) (CEfiTime *time,
                                CEfiTimeCapabilities *capabilities);
        CEfiStatus (*set_time) (CEfiTime *time);
        CEfiStatus (*get_wakeup_time) (CEfiBool *enabled,
                                       CEfiBool *pending,
                                       CEfiTime *time);
        CEfiStatus (*set_wakeup_time) (CEfiBool enable,
                                       CEfiTime *time);

        CEfiStatus (*set_virtual_address_map) (CEfiUSize memory_map_size,
                                               CEfiUSize descriptor_size,
                                               CEfiU32 descriptor_version,
                                               CEfiMemoryDescriptor *virtual_map);
        CEfiStatus (*convert_pointer) (CEfiUSize debug_disposition,
                                       void **address);

        CEfiStatus (*get_variable) (CEfiChar16 *variable_name,
                                    CEfiGuid *vendor_guid,
                                    CEfiU32 *attributes,
                                    CEfiUSize *data_size,
                                    void *data);
        CEfiStatus (*get_next_variable_name) (CEfiUSize *variable_name_size,
                                              CEfiChar16 *variable_name,
                                              CEfiGuid *vendor_guid);
        CEfiStatus (*set_variable) (CEfiChar16 *variable_name,
                                    CEfiGuid *vendor_guid,
                                    CEfiU32 attributes,
                                    CEfiUSize data_size,
                                    void *data);

        CEfiStatus (*get_next_high_mono_count) (CEfiU32 *high_count);
        void (*reset_system) (CEfiResetType reset_type,
                              CEfiStatus reset_status,
                              CEfiUSize data_size,
                              void *reset_data);

        CEfiStatus (*update_capsule) (CEfiCapsuleHeader **capsule_header_array,
                                      CEfiUSize capsule_count,
                                      CEfiPhysicalAddress scatter_gather_list);
        CEfiStatus (*query_capsule_capabilities) (CEfiCapsuleHeader **capsule_header_array,
                                                  CEfiUSize capsule_count,
                                                  CEfiU64 *maximum_capsule_size,
                                                  CEfiResetType *reset_type);

        CEfiStatus (*query_variable_info) (CEfiU32 attributes,
                                           CEfiU64 *maximum_variable_storage_size,
                                           CEfiU64 *remaining_variable_storage_size,
                                           CEfiU64 *maximum_variable_size);
} CEfiRuntimeServices;

#define C_EFI_BOOT_SERVICES_SIGNATURE C_EFI_U64_C(0x56524553544f4f42) /* "BOOTSERV" */

typedef struct CEfiBootServices {
        CEfiTableHeader hdr;

        CEfiTpl (*raise_tpl) (CEfiTpl new_tpl);
        void (*restore_tpl) (CEfiTpl old_tpl);

        CEfiStatus (*allocate_pages) (CEfiAllocateType type,
                                      CEfiMemoryType memory_type,
                                      CEfiUSize pages,
                                      CEfiPhysicalAddress *memory);
        CEfiStatus (*free_pages) (CEfiPhysicalAddress memory,
                                  CEfiUSize pages);
        CEfiStatus (*get_memory_map) (CEfiUSize *memory_map_size,
                                      CEfiMemoryDescriptor *memory_map,
                                      CEfiUSize *map_key,
                                      CEfiUSize *descriptor_size,
                                      CEfiU32 *descriptor_version);
        CEfiStatus (*allocate_pool) (CEfiMemoryType pool_type,
                                     CEfiUSize size,
                                     void **buffer);
        CEfiStatus (*free_pool) (void *buffer);

        CEfiStatus (*create_event) (CEfiU32 type,
                                    CEfiTpl notify_tpl,
                                    CEfiEventNotify notify_function,
                                    void *notify_context,
                                    CEfiEvent *event);
        CEfiStatus (*set_timer) (CEfiEvent event,
                                 CEfiTimerDelay type,
                                 CEfiU64 trigger_time);
        CEfiStatus (*wait_for_event) (CEfiUSize number_of_events,
                                      CEfiEvent *event,
                                      CEfiUSize *index);
        CEfiStatus (*signal_event) (CEfiEvent event);
        CEfiStatus (*close_event) (CEfiEvent event);
        CEfiStatus (*check_event) (CEfiEvent event);

        CEfiStatus (*install_protocol_interface) (CEfiHandle *handle,
                                                  CEfiGuid *protocol,
                                                  CEfiInterfaceType interface_type,
                                                  void *interface);
        CEfiStatus (*reinstall_protocol_interface) (CEfiHandle handle,
                                                    CEfiGuid *protocol,
                                                    void *old_interface,
                                                    void *new_interface);
        CEfiStatus (*uninstall_protocol_interface) (CEfiHandle handle,
                                                    CEfiGuid *protocol,
                                                    void *interface);
        CEfiStatus (*handle_protocol) (CEfiHandle handle,
                                       CEfiGuid *protocol,
                                       void **interface);
        void *reserved;
        CEfiStatus (*register_protocol_notify) (CEfiGuid *protocol,
                                                CEfiEvent event,
                                                void **registration);
        CEfiStatus (*locate_handle) (CEfiLocateSearchType search_type,
                                     CEfiGuid *protocol,
                                     void *search_key,
                                     CEfiUSize *buffer_size,
                                     CEfiHandle *buffer);
        CEfiStatus (*locate_device_path) (CEfiGuid *protocol,
                                          CEfiDevicePathProtocol **device_path,
                                          CEfiHandle *device);

        CEfiStatus (*install_configuration_table) (CEfiGuid *guid,
                                                   void *table);

        CEfiStatus (*load_image) (CEfiBool boot_policy,
                                  CEfiHandle parent_image_handle,
                                  CEfiDevicePathProtocol *device_path,
                                  void *source_buffer,
                                  CEfiUSize source_size,
                                  CEfiHandle *image_handle);
        CEfiStatus (*start_image) (CEfiHandle image_handle,
                                   CEfiUSize *exit_data_size,
                                   CEfiChar16 **exit_data);
        CEfiStatus (*exit) (CEfiHandle image_handle,
                            CEfiStatus exit_status,
                            CEfiUSize exit_data_size,
                            CEfiChar16 *exit_data);
        CEfiStatus (*unload_image) (CEfiHandle image_handle);
        CEfiStatus (*exit_boot_services) (CEfiHandle image_handle,
                                          CEfiUSize map_key);

        CEfiStatus (*get_next_monotonic_count) (CEfiU64 *count);
        CEfiStatus (*stall) (CEfiUSize microseconds);
        CEfiStatus (*set_watchdog_timer) (CEfiUSize timeout,
                                          CEfiU64 watchdog_code,
                                          CEfiUSize data_size,
                                          CEfiChar16 *watchdog_data);

        /* 1.1+ */

        CEfiStatus (*connect_controller) (CEfiHandle controller_handle,
                                          CEfiHandle *driver_image_handle,
                                          CEfiDevicePathProtocol *remaining_device_path,
                                          CEfiBool recursive);
        CEfiStatus (*disconnect_controller) (CEfiHandle controller_handle,
                                             CEfiHandle driver_image_handle,
                                             CEfiHandle child_handle);

        CEfiStatus (*open_protocol) (CEfiHandle handle,
                                     CEfiGuid *protocol,
                                     void **interface,
                                     CEfiHandle agent_handle,
                                     CEfiHandle controller_handle,
                                     CEfiU32 attributes);
        CEfiStatus (*close_protocol) (CEfiHandle handle,
                                      CEfiGuid *protocol,
                                      CEfiHandle agent_handle,
                                      CEfiHandle controller_handle);
        CEfiStatus (*open_protocol_information) (CEfiHandle handle,
                                                 CEfiGuid *protocol,
                                                 CEfiOpenProtocolInformationEntry **entry_buffer,
                                                 CEfiUSize *entry_count);

        CEfiStatus (*protocols_per_handle) (CEfiHandle handle,
                                            CEfiGuid ***protocol_buffer,
                                            CEfiUSize *protocol_buffer_count);
        CEfiStatus (*locate_handle_buffer) (CEfiLocateSearchType search_type,
                                            CEfiGuid *protocol,
                                            void *search_key,
                                            CEfiUSize *no_handles,
                                            CEfiHandle **buffer);
        CEfiStatus (*locate_protocol) (CEfiGuid *protocol,
                                       void *registration,
                                       void **interface);
        CEfiStatus (*install_multiple_protocol_interfaces) (CEfiHandle *handle,
                                                            ...);
        CEfiStatus (*uninstall_multiple_protocol_interfaces) (CEfiHandle handle,
                                                              ...);

        CEfiStatus (*calculate_crc32) (void *data,
                                       CEfiUSize data_size,
                                       CEfiU32 *crc32);

        void (*copy_mem) (void *destination,
                          void *source,
                          CEfiUSize length);
        void (*set_mem) (void *buffer,
                         CEfiUSize size,
                         CEfiU8 value);

        /* 2.0+ */

        CEfiStatus (*create_event_ex) (CEfiU32 type,
                                       CEfiTpl notify_tpl,
                                       CEfiEventNotify notify_function,
                                       void *notify_context,
                                       CEfiGuid *event_group,
                                       CEfiEvent *event);
} CEfiBootServices;

#define C_EFI_SYSTEM_TABLE_SIGNATURE C_EFI_U64_C(0x5453595320494249) /* "IBI SYST" */

typedef struct CEfiSystemTable {
        CEfiTableHeader hdr;
        CEfiChar16 *firmware_vendor;
        CEfiU32 firmware_revision;

        CEfiHandle console_in_handle;
        CEfiSimpleTextInputProtocol *con_in;
        CEfiHandle console_out_handle;
        CEfiSimpleTextOutputProtocol *con_out;
        CEfiHandle standard_error_handle;
        CEfiSimpleTextOutputProtocol *std_err;

        CEfiRuntimeServices *runtime_services;
        CEfiBootServices *boot_services;

        CEfiUSize number_of_table_entries;
        CEfiConfigurationTable *configuration_table;
} CEfiSystemTable;

#ifdef __cplusplus
}
#endif
