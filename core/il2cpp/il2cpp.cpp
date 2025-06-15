#include "il2cpp.hpp"

#include "../core.hpp"

#include "../../utilities/memory/memory.hpp"
#include "../../utilities/encrypt/encrypt.hpp"
#include "../../utilities/value/value.hpp"
#include "../../utilities/process/process.hpp"
#include "../../utilities/hash/hash.hpp"
#include "../../utilities/definitions/definitions.hpp"

namespace il2cpp {
	namespace impl {
		uint64_t il2cpp_field_static_get_value( uint64_t field, uint64_t* pvalue ) {
			static decltype( &il2cpp_field_static_get_value ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_field_static_get_value" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_field_static_get_value ) >( rva( address, 1, 5 ) );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( field, pvalue );
		}

		uint64_t il2cpp_method_get_param_count( uint64_t method ) {
			return memory::read< uint8_t >( method + o( 0x52 ) );
		}

		uint64_t* il2cpp_domain_get_assemblies( uint64_t domain, size_t* psize ) {
			static uint64_t assemblies{ };
			static uint64_t pointer{ };

			if ( !assemblies
				 || !pointer ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_domain_get_assemblies" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				pointer = rva( address, 3, 7 );
				assemblies = pointer - o( 8 );
			}

			const auto& size = ( memory::read< uint64_t >( pointer ) - memory::read< uint64_t >( assemblies ) ) >> 3;

			if ( psize )
				*psize = size;

			return reinterpret_cast< uint64_t* >( memory::read< uint64_t >( assemblies ) );
		}

		uint64_t il2cpp_assembly_get_image( uint64_t assembly ) {
			return memory::read< uint64_t >( assembly );
		}

		uint64_t il2cpp_class_get_methods( uint64_t klass, size_t* psize ) {
			static decltype( &il2cpp_class_get_methods ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_class_get_methods" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_class_get_methods ) >( address );

				if ( !memory::is_valid( function ) ) 
					return 0;
			}

			return function( klass, psize );
		}

		uint64_t il2cpp_class_get_fields( uint64_t klass, size_t* psize ) {
			static decltype( &il2cpp_class_get_fields ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_class_get_fields" ) );

				if ( !memory::is_valid( address ) ) 
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_class_get_fields ) >( address );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( klass, psize );
		}

		uint64_t il2cpp_field_get_offset( uint64_t field ) {
			return memory::read< int >( field + o( 0x18 ) );
		}

		uint64_t il2cpp_type_get_object( uint64_t type ) {
			static decltype( &il2cpp_type_get_object ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_type_get_object" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_type_get_object ) >( rva( address, 1, 5 ) );

				if ( !memory::is_valid( function ) ) 
					return 0;
			}

			return function( type );
		}

		uint64_t il2cpp_class_from_name( uint64_t image, const char* space, const char* name ) {
			static decltype( &il2cpp_class_from_name ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_class_from_name" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_class_from_name ) >( rva( address, 1, 5 ) );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( image, space, name );
		}

		uint64_t il2cpp_class_get_type( uint64_t klass ) {
			return klass + o( 0x20 );
		}

		uint64_t il2cpp_method_get_name( uint64_t method ) {
			return memory::read< uint64_t >( method + o( 0x18 ) );
		}

		uint64_t il2cpp_field_get_name( uint64_t field ) {
			return memory::read< uint64_t >( field );
		}

		uint64_t il2cpp_resolve_icall( const char* name ) {
			static decltype( &il2cpp_resolve_icall ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_resolve_icall" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_resolve_icall ) >( rva( address, 1, 5 ) );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( name );
		}

		uint64_t il2cpp_string_new( const char* str ) {
			static decltype( &il2cpp_string_new ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_string_new" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_string_new ) >( address );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( str );
		}

		uint64_t il2cpp_object_new( uint64_t type ) {
			static decltype( &il2cpp_object_new ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_object_new" ) );

				if ( !memory::is_valid( address ) ) 
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_object_new ) >( rva( address + o( 4 ), 1, 5 ) );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( type );
		}

		uint64_t il2cpp_domain_get( ) {
			static uint64_t function{ };
			static uint64_t domain{ };

			if ( !domain ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_domain_get" ) );;

				if ( !memory::is_valid( address ) )
					return 0;

				function = rva( address, 1, 5 );

				if ( !memory::is_valid( function ) ) 
					return 0;

				domain = rva( function + o( 4 ), 3, 7 );

				if ( !memory::is_valid( domain ) )
					return 0;
			}

			const auto& result = memory::read< uint64_t >( domain );

			if ( !memory::is_valid( result ) )
				return reinterpret_cast< uint64_t( * )( ) >( function )( );

			return result;
		}

		uint64_t il2cpp_gchandle_get_target( uint32_t handle ) {
			static decltype( &il2cpp_gchandle_get_target ) function{ };

			if ( !function ) {
				const auto& address = process::find_export( game_assembly, HASH( "il2cpp_gchandle_get_target" ) );

				if ( !memory::is_valid( address ) )
					return 0;

				function = reinterpret_cast< decltype( &il2cpp_gchandle_get_target ) >( rva( address, 1, 5 ) );

				if ( !memory::is_valid( function ) )
					return 0;
			}

			return function( handle );
		}
	}

	uint64_t field_static_get_value( uint64_t field, uint64_t* pvalue ) {
		return impl::il2cpp_field_static_get_value( field, pvalue );
	}

	uint64_t method_get_param_count( uint64_t method ) {
		return impl::il2cpp_method_get_param_count( method );
	}

	uint64_t* domain_get_assemblies( uint64_t domain, size_t* psize ) {
		return impl::il2cpp_domain_get_assemblies( domain, psize );
	}

	uint64_t assembly_get_image( uint64_t assembly ) {
		return impl::il2cpp_assembly_get_image( assembly );
	}

	uint64_t class_get_methods( uint64_t klass, size_t* psize ) {
		return impl::il2cpp_class_get_methods( klass, psize );
	}

	uint64_t class_get_fields( uint64_t klass, size_t* psize ) {
		return impl::il2cpp_class_get_fields( klass, psize );
	}

	uint64_t field_get_offset( uint64_t field ) {
		return impl::il2cpp_field_get_offset( field );
	}

	uint64_t type_get_object( uint64_t type ) {
		return impl::il2cpp_type_get_object( type );
	}

	uint64_t class_from_name( uint64_t image, const char* space, const char* name ) {
		return impl::il2cpp_class_from_name( image, space, name );
	}

	uint64_t class_get_type( uint64_t klass ) {
		return impl::il2cpp_class_get_type( klass );
	}

	uint64_t method_get_name( uint64_t method ) {
		return impl::il2cpp_method_get_name( method );
	}

	uint64_t field_get_name( uint64_t field ) {
		return impl::il2cpp_field_get_name( field );
	}

	uint64_t resolve_icall( const char* name ) {
		return impl::il2cpp_resolve_icall( name );
	}

	uint64_t string_new( const char* str ) {
		return impl::il2cpp_string_new( str );
	}

	uint64_t object_new( uint64_t type ) {
		return impl::il2cpp_object_new( type );
	}

	uint64_t domain_get( ) {
		return impl::il2cpp_domain_get( );
	}

	uint64_t gchandle_get_target( uint32_t handle ) {
		return impl::il2cpp_gchandle_get_target( handle );
	}
}