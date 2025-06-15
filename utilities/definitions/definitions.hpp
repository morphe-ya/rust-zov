#pragma once

#include "../../includes/includes.hpp"
#include "../value/value.hpp"

#include <winternl.h>

#define rva( ptr, offset, size ) ( ( const uint64_t )( ptr + *( int32_t* )( ( uint8_t* )ptr + offset ) + size ) )
#define offset( ptr, size ) ( ptr + size + *( int32_t *)( ptr + size ) + sizeof( int32_t ) )

#define to_lower( chr ) ( ( chr >= o( 'A' ) && chr <= o( 'Z' ) ) ? ( chr + o( 32 ) ) : chr )

extern "C" {
	typedef struct _peb_ldr_data_t {
		uint32_t m_length;
		uint32_t m_initialized;

		const char* m_ss_handle;

		LIST_ENTRY m_in_load_order_module_list;
		LIST_ENTRY m_in_memory_order_module_list;
		LIST_ENTRY m_in_initialization_order_module_list;
	} peb_ldr_data_t, * ppeb_ldr_data_t;

	typedef struct _peb_t {
		uint8_t reserved1[ 2 ];
		uint8_t m_being_debugged;
		uint8_t reserved2[ 1 ];

		const char* reserved3[ 2 ];
		ppeb_ldr_data_t m_ldr;
	} peb_t, * ppeb_t;

	typedef struct _ldr_data_table_entry_t {
		LIST_ENTRY m_in_load_order_module_list;
		LIST_ENTRY m_in_memory_order_links;
		LIST_ENTRY m_in_initialization_order_module_list;

		uint64_t m_dll_base;
		uint64_t m_entry_point;

		union {
			uint32_t m_size_of_image;
			const char* reserved;
		};

		UNICODE_STRING m_full_dll_name;
		UNICODE_STRING m_base_dll_name;
	} ldr_data_table_entry_t, * pldr_data_table_entry_t;

    typedef struct _ksystem_time_t {
        uint32_t m_low_part;
        int32_t m_high1_time;
        int32_t m_high2_time;
    } ksystem_time_t, * pksystem_time_t;

    typedef enum _nt_product_type_t {
        nt_product_win_nt = 1,
        nt_product_lan_man_nt,
        nt_product_server
    } nt_product_type_t, * p_nt_product_type_t;

    typedef enum _alternative_architecture_t {
        standard_design,
        nec98_x86,
        end_alternatives
    } alternative_architecture_t;

    typedef struct _kuser_shared_data_t {
        uint32_t m_tick_count_low_deprecated;
        uint32_t m_tick_count_multiplier;
        volatile ksystem_time_t m_interrupt_time;
        volatile ksystem_time_t m_system_time;
        volatile ksystem_time_t m_time_zone_bias;
        uint16_t m_image_number_low;
        uint16_t m_image_number_high;
        wchar_t m_nt_system_root[ 260 ];
        uint32_t m_max_stack_trace_depth;
        uint32_t m_crypto_exponent;
        uint32_t m_time_zone_id;
        uint32_t m_large_page_minimum;
        uint32_t m_reserved2[ 7 ];
        nt_product_type_t m_nt_product_type;
        uint8_t m_product_type_is_valid;
        uint32_t m_nt_major_version;
        uint32_t m_nt_minor_version;
        uint8_t m_processor_features[ 64 ];
        uint32_t m_reserved1;
        uint32_t m_reserved3;
        volatile uint32_t m_time_slip;
        alternative_architecture_t m_alternative_architecture;
        LARGE_INTEGER m_system_expiration_date;
        uint32_t m_suite_mask;
        uint8_t m_kd_debugger_enabled;
        uint8_t m_nx_support_policy;
        volatile uint32_t m_active_console_id;
        volatile uint32_t m_dismount_count;
        uint32_t m_com_plus_package;
        uint32_t m_last_system_rit_event_tick_count;
        uint32_t m_number_of_physical_pages;
        uint8_t m_safe_boot_mode;
        uint32_t m_trace_logging;
        uint64_t m_test_ret_instruction;
        uint32_t m_system_call;
        uint32_t m_system_call_return;
        uint64_t m_system_call_pad[ 3 ];

        union {
            volatile ksystem_time_t m_tick_count;
            volatile uint64_t m_tick_count_quad;
        } dummy_union_name;

        uint32_t m_cookie;
        uint32_t m_wow64_shared_information[ 16 ];
    } kshared_user_data_t, * pkshared_user_data_t;

    typedef struct _handle_file_t {
        HANDLE m_file;
    } handle_file_t, * phandle_file_t;
}