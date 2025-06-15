#include "sdk.hpp"

#include "../../utilities/memory/memory.hpp"

#include "../il2cpp/il2cpp.hpp"

namespace sdk {
	namespace unity {
		uint64_t new_string( const char* str ) {
			return il2cpp::string_new( str );
		}

		uint64_t method( const char* _name, const char* _method, int _count, const char* _arg_name, int selected, const char* space ) {
			const auto& klass = sdk::unity::klass( _name, space );

			if ( !memory::is_valid( klass ) )
				return 0;

			uint64_t method{ };
			size_t size{ };

			while ( method = il2cpp::class_get_methods( klass, &size ) ) {
				const auto& name = reinterpret_cast< const char* >( il2cpp::method_get_name( method ) );

				if ( !memory::is_valid( name ) )
					continue;

				if ( stricmp( name, _method ) )
					continue;

				if ( selected >= 0 && _arg_name ) {
					const auto& args = memory::read< uint64_t >( method + o( 0x28 ) );
					const auto& count = il2cpp::method_get_param_count( method );

					if ( selected > count 
						 || ( _count >= 0 && count != _count ) )
						continue;

					char* arg_name{ };

					if ( count > 0 )
						arg_name = memory::read< char* >( args + ( selected - 1 ) * o( 0x18 ) );
					else
						arg_name = nullptr;

					if ( !memory::is_valid( arg_name ) )
						break;
				}

				return method;
			}

			return 0;
		}

		uint64_t field( const char* _name, const char* _field, bool offset, const char* space ) {
			const auto& klass = sdk::unity::klass( _name, space );

			if ( !memory::is_valid( klass ) )
				return 0;

			uint64_t field{ };
			size_t size{ };

			while ( field = il2cpp::class_get_fields( klass, &size ) ) {
				const auto& name = reinterpret_cast< const char* >( il2cpp::field_get_name( field ) );

				if ( !memory::is_valid( name ) )
					continue;

				if ( strcmp( name, _field ) )
					continue;

				if ( !offset )
					return field;

				return il2cpp::field_get_offset( field );
			}

			return 0;
		}

		uint64_t value( const char* _name, const char* _field, const char* space ) {
			const auto& klass = sdk::unity::klass( _name, space );

			if ( !memory::is_valid( klass ) )
				return 0;

			uint64_t field{ };
			size_t size{ };

			while ( field = il2cpp::class_get_fields( klass, &size ) ) {
				const auto& name = reinterpret_cast< const char* >( il2cpp::field_get_name( field ) );

				if ( !memory::is_valid( name ) )
					continue;

				if ( stricmp( name, _field ) )
					continue;

				uint64_t value{ };
				il2cpp::field_static_get_value( field, &value );

				return value;
			}

			return 0;
		}

		uint64_t klass( const char* name, const char* space ) {
			const auto& domain = il2cpp::domain_get( );

			if ( !memory::is_valid( domain ) )
				return 0;

			size_t size{ };
			const auto& assemblies = il2cpp::domain_get_assemblies( domain, &size );

			if ( !memory::is_valid( assemblies ) )
				return 0;

			for ( int i{ }; i < size; ++i ) {
				const auto& image = il2cpp::assembly_get_image( assemblies[ i ] );

				if ( !memory::is_valid( assemblies ) )
					continue;

				const auto& klass = il2cpp::class_from_name( image, space, name );

				if ( !memory::is_valid( klass ) )
					continue;

				return klass;
			}

			return 0;
		}

		uint64_t icall( const char* name ) {
			return il2cpp::resolve_icall( name );
		}

		uint64_t type( const char* name, const char* space ) {
			const auto& klass = sdk::unity::klass( name, space );

			if ( !memory::is_valid( klass ) )
				return 0;

			return il2cpp::type_get_object( il2cpp::class_get_type( klass ) );
		}
	}
}