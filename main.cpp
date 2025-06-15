#include "includes/includes.hpp"

#include "core/core.hpp"

int __stdcall DllMain( uint64_t allocated, uint32_t call_reason, void* lpv_reserved ) {
	if ( call_reason != 1 )
		return false;

	core::initialize( );

	return true;
}