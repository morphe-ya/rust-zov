#pragma once

#include "../../includes/includes.hpp"

namespace il2cpp {
	namespace impl {
		uint64_t il2cpp_field_static_get_value( uint64_t, uint64_t* );
		uint64_t il2cpp_method_get_param_count( uint64_t );
		uint64_t* il2cpp_domain_get_assemblies( uint64_t, size_t* );
		uint64_t il2cpp_assembly_get_image( uint64_t );
		uint64_t il2cpp_class_get_methods( uint64_t, size_t* );
		uint64_t il2cpp_class_get_fields( uint64_t, size_t* );
		uint64_t il2cpp_field_get_offset( uint64_t );
		uint64_t il2cpp_type_get_object( uint64_t );
		uint64_t il2cpp_class_from_name( uint64_t, const char*, const char* );
		uint64_t il2cpp_class_get_type( uint64_t );
		uint64_t il2cpp_field_get_name( uint64_t );
		uint64_t il2cpp_resolve_icall( const char* );
		uint64_t il2cpp_string_new( const char* );
		uint64_t il2cpp_object_new( uint64_t );
		uint64_t il2cpp_domain_get( );
		uint64_t il2cpp_gchandle_get_target( uint32_t );
	}

	uint64_t field_static_get_value( uint64_t, uint64_t* );
	uint64_t method_get_param_count( uint64_t );
	uint64_t* domain_get_assemblies( uint64_t, size_t* );
	uint64_t assembly_get_image( uint64_t );
	uint64_t class_get_methods( uint64_t, size_t* );
	uint64_t class_get_fields( uint64_t, size_t* );
	uint64_t field_get_offset( uint64_t );
	uint64_t type_get_object( uint64_t );
	uint64_t class_from_name( uint64_t, const char*, const char* );
	uint64_t class_get_type( uint64_t );
	uint64_t method_get_name( uint64_t );
	uint64_t field_get_name( uint64_t );
	uint64_t resolve_icall( const char* );
	uint64_t string_new( const char* );
	uint64_t object_new( uint64_t );
	uint64_t domain_get( );
	uint64_t gchandle_get_target( uint32_t );
}