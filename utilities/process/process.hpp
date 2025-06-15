#pragma once

#include "../../includes/includes.hpp"

namespace process {
	uint64_t get_module_base( uint64_t );

	uint64_t find_import( uint64_t, uint64_t );
	uint64_t find_export( uint64_t, uint64_t );

	HANDLE get_current_process_token( );

	uint32_t get_current_process_id( );
	uint32_t get_current_thread_id( );

	HANDLE get_current_process( );
	HANDLE get_current_thread( );

	HANDLE get_process_heap( );
}